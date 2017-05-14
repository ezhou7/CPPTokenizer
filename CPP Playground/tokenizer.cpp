//
//  tokenizer.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "tokenizer.hpp"

Tokenizer::Tokenizer() {
    abbrev = unique_ptr<Abbreviation>(new Abbreviation);
    eng_apos = unique_ptr<EnglishApostrophe>(new EnglishApostrophe);
}

Tokenizer::~Tokenizer() {
    
}

bool Tokenizer::is_whitespace(const char& c) {
    return c == CharConst::SPACE || c == CharConst::TAB || c == CharConst::NEWLINE;
}

bool Tokenizer::is_terminal(const char& c) {
    return c == CharConst::PERIOD || c == CharConst::EXCLAMATION || c == CharConst::QUESTION;
}

bool Tokenizer::is_conjunctive(const char& c) {
    return c == CharConst::COMMA || c == CharConst::COLON || c == CharConst::SEMICOLON;
}

bool Tokenizer::is_apostrophe(const char& c) {
    return c == CharConst::APOSTROPHE;
}

bool Tokenizer::is_abbreviation(const string& s) {
    return abbrev->is_abbreviation(s);
}

bool Tokenizer::is_ellipsis(const string& s, int pos) {
    return s[pos] == CharConst::PERIOD &&
           s[pos + 1] == CharConst::PERIOD &&
           s[pos + 2] == CharConst::PERIOD;
}

bool Tokenizer::is_opener(const char& c) {
    return c == CharConst::DOUBLE_QUOTE ||
           c == CharConst::LEFT_PARENS ||
           c == CharConst::LEFT_BRACKET ||
           c == CharConst::LEFT_BRACE;
}

bool Tokenizer::is_encloser(const char& c) {
    return c == CharConst::DOUBLE_QUOTE ||
    c == CharConst::RIGHT_PARENS ||
    c == CharConst::RIGHT_BRACKET ||
    c == CharConst::RIGHT_BRACE;
}

vector<string *>* Tokenizer::tokenize(const string& text) {
    auto tokens = new vector<string *>();
    
    int prev = 0;
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        
        if (is_whitespace(c)) {
            // ignore contiguous chunks of whitespace
            if (prev != i)
                tokens->push_back(new string(text.substr(prev, i - prev)));
            
            prev = i + 1;
        } else if (is_terminal(c)) {
            // check if is abbreviation
            if (is_abbreviation(boost::to_lower_copy(text.substr(prev, i - prev)))) {
                tokens->push_back(new string(text.substr(prev, i - prev + 1)));
                prev = i + 1;
                continue;
            }
            
            // append token before terminal punctuation
            if (i - 1 > 0 && !is_terminal(text[i - 1])) {
                tokens->push_back(new string(text.substr(prev, i - prev)));
                prev = i;
            }
            
            // treat consecutive terminal punctations as one tokens
            if (i + 1 < text.size() && !is_terminal(text[i + 1])) {
                tokens->push_back(new string(text.substr(prev, i - prev + 1)));
                prev = i + 1;
            }
        } else if (is_conjunctive(c)) {
            // don't push empty strings
            if (prev != i)
                tokens->push_back(new string(text.substr(prev, i - prev)));
            
            tokens->push_back(new string(1, c));
            
            prev = i + 1;
        } else if (is_apostrophe(c)) {
            int suf_len = eng_apos->is_apostrophe_suffix(text, i + 1);
            
            // if there exists an apostrophe suffix, then suf_len > 0
            if (suf_len) {
                if (prev != i)
                    tokens->push_back(new string(text.substr(prev, i - prev)));
                
                tokens->push_back(new string(text.substr(i, suf_len + 1)));
            
                prev = i + suf_len + 1;
            } else {
                continue;
            }
        } else if (is_opener(c) || is_encloser(c)) {
            if (prev != i)
                tokens->push_back(new string(text.substr(prev, i - prev)));
            
            tokens->push_back(new string(1, c));
            
            prev = i + 1;
        }
    }
    
    tokens->push_back(new string(text.substr(prev, text.size() - prev)));
    
    return tokens;
}

vector<string *>* Tokenizer::split_whitespace(const string& sentence) {
    auto token_primitives = new vector<string *>();
    
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

vector<string *>* Tokenizer::segmentize(const string& text) {
    auto sentence_primitives = new vector<string *>();
    
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
