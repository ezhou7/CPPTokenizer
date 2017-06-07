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
}

Tokenizer::~Tokenizer() {
    
}

bool Tokenizer::is_whitespace(const char& c) {
    return CharUtils::is_whitespace(c);
}

bool Tokenizer::is_terminal(const char& c) {
    return CharUtils::is_terminal(c);
}

bool Tokenizer::is_conjunctive(const char& c) {
    return CharUtils::is_conjunctive(c);
}

bool Tokenizer::is_apostrophe(const char& c) {
    return CharUtils::is_apostrophe(c);
}

bool Tokenizer::is_opener(const char& c) {
    return CharUtils::is_opener(c);
}

bool Tokenizer::is_encloser(const char& c) {
    return CharUtils::is_encloser(c);
}

bool Tokenizer::is_abbreviation(const string& s) {
    return abbrev->is_abbreviation(s);
}

bool Tokenizer::is_ellipsis(const string& s, int pos) {
    return s[pos] == CharConst::PERIOD &&
           s[pos + 1] == CharConst::PERIOD &&
           s[pos + 2] == CharConst::PERIOD;
}

bool Tokenizer::is_emoticon(const string& s) {
    return emoticon->is_emoticon(s);
}

int Tokenizer::is_emoticon(const string& s, const int pos) {
    return emoticon->is_emoticon(s, pos);
}

bool Tokenizer::is_compound(const string& s) {
    return compound->is_compound(s);
}

str_t Tokenizer::substring(const string& s, int start, int end) {
    return StringUtils::substring(s, start, end);
}

void Tokenizer::add_tokens(up_tvec_t& tokens, up_tvec_t& extension) {
    tokens->insert(tokens->end(),
                   make_move_iterator(extension->begin()),
                   make_move_iterator(extension->end()));
}

up_tvec_t Tokenizer::tokenize(const string& text) {
    auto tokens = up_tvec_t(new vector<up_token_t>());
    
    int prev = 0, text_len = (int) text.size();
    for (int i = 0; i < text_len; i++) {
        char c = text[i];
        
        if (is_whitespace(c)) {
            // ignore contiguous chunks of whitespace
            if (prev != i) {
                auto prev_word = text.substr(prev, i - prev);
                auto c_tokens = compound->tokenize(prev_word, prev, i);
                add_tokens(tokens, c_tokens);
            }
            
            prev = i + 1;
        } else if (int k = is_emoticon(text, i)) {
            // push previous token
            if (prev != i) {
                auto prev_word = text.substr(prev, i - prev);
                auto c_tokens = compound->tokenize(prev_word, prev, i);
                add_tokens(tokens, c_tokens);
            }
            
            // treat emoticon as token
            auto emote_str = text.substr(i, k);
            tokens->push_back(up_token_t(new Token(emote_str)));
            
            // need prev = i in next loop instance to trigger prev == i, so i = prev - 1 to combat increment (i++)
            prev = i + k;
            i = prev - 1;
        } else if (is_terminal(c)) {
            // check if is abbreviation
            if (is_abbreviation(boost::to_lower_copy(text.substr(prev, i - prev)))) {
                auto prev_word = text.substr(prev, i - prev + 1);
                auto c_tokens = compound->tokenize(prev_word, prev, i + 1);
                
                add_tokens(tokens, c_tokens);
                prev = i + 1;
                
                continue;
            }
            
            // append token before terminal punctuation
            if (i - 1 > 0 && !is_terminal(text[i - 1])) {
                auto prev_word = text.substr(prev, i - prev);
                auto c_tokens = compound->tokenize(prev_word, prev, i);
                
                add_tokens(tokens, c_tokens);
                prev = i;
            }
            
            // treat consecutive terminal punctations as one tokens
            if (i + 1 < text.size() && !is_terminal(text[i + 1])) {
                auto prev_word = text.substr(prev, i - prev + 1);
                auto c_tokens = compound->tokenize(prev_word, prev, i);
                
                add_tokens(tokens, c_tokens);
                prev = i + 1;
            }
        } else if (is_conjunctive(c)) {
            // don't push empty strings
            if (prev != i) {
                auto prev_word = text.substr(prev, i - prev);
                auto c_tokens = compound->tokenize(prev_word, prev, i);
                add_tokens(tokens, c_tokens);
            }
            
            // push conjunctive punctuation as token
            tokens->push_back(up_token_t(new Token(string(1, c))));
            
            prev = i + 1;
        } else if (is_apostrophe(c)) {
            int suf_len = eng_apos->is_apostrophe_suffix(text, i + 1);
            
            // TODO: definitely is optimizable
            // if there exists an apostrophe suffix, then suf_len > 0; otherwise not apostrophe suffix
            if (suf_len) {
                // if suffix is "n't"
                if (text[i + 1] == 't' && text[i - 1] == 'n') {
                    // add word before suffix "n't"
                    if (prev - 1 != i) {
                        auto prev_word = text.substr(prev, i - prev - 1);
                        auto c_tokens = compound->tokenize(prev_word, prev, i - 1);
                        add_tokens(tokens, c_tokens);
                    }
                    
                    // add suffix itself
                    auto suffix = text.substr(i - 1, 3);
                    tokens->push_back(up_token_t(new Token(suffix)));
                    
                    prev = i + 2;
                } else {
                    // add word before suffix
                    if (prev != i) {
                        auto prev_word = text.substr(prev, i - prev);
                        auto c_tokens = compound->tokenize(prev_word, prev, i);
                        add_tokens(tokens, c_tokens);
                    }
                    
                    // add suffix
                    auto suffix = text.substr(i, suf_len + 1);
                    tokens->push_back(up_token_t(new Token(suffix)));
            
                    prev = i + suf_len + 1;
                }
            }
        } else if (is_opener(c) || is_encloser(c)) {
            if (prev != i) {
                auto prev_word = text.substr(prev, i - prev);
                auto c_tokens = compound->tokenize(prev_word, prev, i);
                add_tokens(tokens, c_tokens);
            }
            
            tokens->push_back(up_token_t(new Token(string(1, c))));
            
            prev = i + 1;
        }
    }
    
    if (prev != text_len) {
        auto prev_word = text.substr(prev, text_len - prev);
        auto c_tokens = compound->tokenize(prev_word, prev, text_len);
        add_tokens(tokens, c_tokens);
    }
    
    return tokens;
}

/* ------------------- Deprecated ------------------- */

uptr_t<vector<up_token_t>> Tokenizer::compound_experimental(const string& s) {
    auto tokens = uptr_t<vector<up_token_t>>(new vector<up_token_t>());
    token_t token;
    
    if (is_compound(s)) {
        auto split_tokens = compound->get_words(s);
        
        for (int i = 0; i < split_tokens->size(); i++) {
            token = new Token(*(*split_tokens)[i]);
            tokens->push_back(up_token_t(token));
        }
    } else {
        token = new Token(s);
        tokens->push_back(up_token_t(token));
    }
    
    return tokens;
}

vector<str_t>* Tokenizer::split_whitespace(const string& sentence) {
    auto token_primitives = new vector<str_t>();
    
    int prev = 0;
    for (int i = 0; i < sentence.size(); i++) {
        char c = sentence[i];
        
        if (is_whitespace(c)) {
            if (prev - i == 0) {
                prev = i + 1;
                continue;
            }
            
            auto str = new string(sentence.substr(prev, i - prev));
            token_primitives->push_back(str);
            
            prev = i + 1;
        }
    }
    
    token_primitives->push_back(new string(sentence.substr(prev, sentence.size() - prev)));
    
    return token_primitives;
}

vector<str_t>* Tokenizer::segmentize(const string& text) {
    auto sentence_primitives = new vector<str_t>();
    
    int prev = 0;
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        
        if (is_terminal(c)) {
            if (is_ellipsis(text, i)) {
                i += 3;
                
                // if whitespace or capital letter follows ellipsis, usually sign of sentence end
                if (is_whitespace(text[i]) || isupper(text[i])) {
                    auto str = new string(text.substr(prev, i - prev));
                    boost::trim(*str);
                    
                    sentence_primitives->push_back(str);
                    
                    prev = (is_whitespace(text[i])) ? i + 1 : i;
                }
                
                continue;
            }
            
            // capture all tailgating punctuation
            if (i + 1 < text.size() && !is_terminal(text[i + 1])) {
                auto str = new string(text.substr(prev, i - prev + 1));
                boost::trim(*str);
                
                sentence_primitives->push_back(str);
                
                prev = i + 1;
            }
        }
    }
    
    sentence_primitives->push_back(new string(text.substr(prev, text.size() - prev)));
    
    return sentence_primitives;
}
