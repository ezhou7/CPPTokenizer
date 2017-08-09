//
//  tokenizer.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "tokenizer.hpp"

Tokenizer::Tokenizer() {
    abbrev = uptr_t<Abbreviation>(new Abbreviation);
    eng_apos = uptr_t<EnglishApostrophe>(new EnglishApostrophe);
    emoticon = uptr_t<Emoticon>(new Emoticon);
    compound = uptr_t<Compound>(new Compound);
    currency = uptr_t<Currency>(new Currency);
}

Tokenizer::~Tokenizer() {
    
}

void Tokenizer::add_tokens(up_tvec_t& tokens, up_tvec_t& extension) {
    tokens->insert(tokens->end(),
                   make_move_iterator(extension->begin()),
                   make_move_iterator(extension->end()));
}

up_tvec_t Tokenizer::TokenizeByWhitespace(const string& text, int prev, int curr) {
    return TokenizePreviousWord(text, prev, curr);
}

up_tvec_t Tokenizer::TokenizeEmoticon(const string& text, int prev, int curr) {
    auto tokens = TokenizePreviousWord(text, prev, curr);
    
    if (int k = emoticon->is_emoticon(text, curr)) {
        auto emote_str = text.substr(curr, k);
        tokens->push_back(up_token_t(new Token(emote_str, curr, curr + k)));
    }
    
    return tokens;
}

up_tvec_t Tokenizer::TokenizeByTerminal(const string& text, int prev, int curr) {
    int end = curr;
    
    // if word chunk is abbreviation, include period as one token
    string lowered = boost::to_lower_copy(text.substr(prev, curr - prev));
    if (text[curr] == CharConst::PERIOD && abbrev->is_abbreviation(lowered)) {
        end++;
    }
    
    auto tokens = TokenizePreviousWord(text, prev, end);
    
    // consider multiple terminals as one token
    int start = end;
    for (end = end + 1; end < text.size(); end++) {
        if (!CharUtils::is_terminal(text[end])) {
            break;
        }
    }
    
    if (start != end) {
        tokens->push_back(up_token_t(new Token(text.substr(start, end - start), start, end)));
    }
    
    return tokens;
}

up_tvec_t Tokenizer::TokenizeConjunctive(const string& text, int prev, int curr) {
    auto tokens = TokenizePreviousWord(text, prev, curr);
    
    // push conjunctive punctuation as token
    tokens->push_back(up_token_t(new Token(string(1, text[curr]), curr, curr + 1)));
    
    return tokens;
}

up_tvec_t Tokenizer::TokenizeByApostrophe(const string& text, int prev, int curr) {
    int suf_len = eng_apos->is_apostrophe_suffix(text, curr + 1);
    token_t suffix = nullptr;
    
    int end = curr;
    // if there exists an apostrophe suffix, then suf_len > 0; otherwise not apostrophe suffix
    if (suf_len) {
        // if suffix is "n't"
        if (text[curr - 1] == 'n' && text[curr + 1] == 't') {
            suffix = new Token(text.substr(curr - 1, 3), curr - 1, curr + 2);
            end--;
        } else {
            suffix = new Token(text.substr(curr, suf_len + 1), curr, curr + suf_len + 1);
        }
    }
    
    auto tokens = TokenizePreviousWord(text, prev, end);
    if (suf_len && suffix != nullptr) {
        tokens->push_back(up_token_t(suffix));
    }
    
    return tokens;
}

up_tvec_t Tokenizer::TokenizeParentheses(const string& text, int prev, int curr) {
    auto tokens = TokenizePreviousWord(text, prev, curr);
    tokens->push_back(up_token_t(new Token(string(1, text[curr]), curr, curr + 1)));
    
    return tokens;
}

up_tvec_t Tokenizer::TokenizeCurrency(const string& text, int prev, int curr) {
    return TokenizeCurrencyAux(text, prev, curr, false);
}

up_tvec_t Tokenizer::TokenizeCurrencyDollars(const string& text, int prev, int curr) {
    return TokenizeCurrencyAux(text, prev, curr, true);
}

up_tvec_t Tokenizer::TokenizeCurrencyAux(const string& text, int prev, int curr, bool isDollarCurrency) {
    auto tokens = TokenizePreviousWord(text, prev, curr);
    int k = (isDollarCurrency) ? currency->is_dollar(text, curr) : currency->is_currency(text, curr);
    
    if (k) {
        tokens->push_back(up_token_t(new Token(text.substr(curr, k), curr, curr + k)));
    }
    
    return tokens;
}

up_tvec_t Tokenizer::TokenizePreviousWord(const string& text, int start, int end) {
    if (start >= end) {
        return up_tvec_t(new vector<up_token_t>());
    }
    
    auto prev_word = text.substr(start, end - start);
    auto c_tokens = compound->tokenize(prev_word, start, end);
    
    return c_tokens;
}

up_tvec_t Tokenizer::tokenize(const string& text) {
    auto all_tokens = up_tvec_t(new vector<up_token_t>());
    
    int prev = 0;
    int text_len = (int) text.size();
    up_tvec_t prev_tokens;
    
    for (int i = 0; i < text_len; i++) {
        char c = text[i];
        
        if (CharUtils::is_whitespace(c)) {
            prev_tokens = TokenizeByWhitespace(text, prev, i);
            add_tokens(all_tokens, prev_tokens);
            
            for (prev = i + 1; prev < text.size(); prev++) {
                if (!CharUtils::is_whitespace(text[prev])) {
                    break;
                }
            }
            
            i = prev - 1;
            continue;
        } else if (int k = emoticon->is_emoticon(text, i)) {
            prev_tokens = TokenizeEmoticon(text, prev, i);
            i += k - 1;
        } else if (CharUtils::is_terminal(c)) {
            prev_tokens = TokenizeByTerminal(text, prev, i);
            i = prev_tokens->back()->getEnd() - 1;
        } else if (CharUtils::is_apostrophe(c)) {
            prev_tokens = TokenizeByApostrophe(text, prev, i);
        } else if (CharUtils::is_opener(c) || CharUtils::is_encloser(c)) {
            prev_tokens = TokenizeParentheses(text, prev, i);
        } else if (CharUtils::is_conjunctive(c)) {
            prev_tokens = TokenizeConjunctive(text, prev, i);
        } else if (int k = currency->is_currency(text, i)) {
            if (i - 1 >= 0 && i + k < text_len && CharUtils::is_whitespace(text[i - 1]) && CharUtils::is_whitespace(text[i + k])) {
                prev_tokens = TokenizeCurrency(text, prev, i);
            } else {
                continue;
            }
        } else if (int k = currency->is_dollar(text, i)) {
            if (i - 1 >= 0 && i + k < text_len && CharUtils::is_whitespace(text[i - 1]) && CharUtils::is_whitespace(text[i + k])) {
                prev_tokens = TokenizeCurrencyDollars(text, prev, i);
            } else {
                continue;
            }
        } else {
            continue;
        }
        
        add_tokens(all_tokens, prev_tokens);
        prev = all_tokens->back()->getEnd();
    }
    
    auto tokens = TokenizePreviousWord(text, prev, text_len);
    add_tokens(all_tokens, tokens);
    
    return all_tokens;
}
