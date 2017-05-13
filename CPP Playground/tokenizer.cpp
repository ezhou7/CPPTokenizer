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
    return c == CharConst::SPACE ||
           c == CharConst::TAB ||
           c == CharConst::NEWLINE;
}

bool Tokenizer::is_terminal_punc(const char& c) {
    return c == CharConst::PERIOD ||
           c == CharConst::EXCLAMATION ||
           c == CharConst::QUESTION;
}

bool Tokenizer::is_conjunctive(const char& c) {
    return c == CharConst::COMMA || c == CharConst::COLON || c == CharConst::SEMICOLON;
}

bool Tokenizer::is_apostrophe(const char& c) {
    return c == CharConst::APOSTROPHE;
}

bool Tokenizer::is_abbreviation(const string& s, int pos) {
    return abbrev->is_abbreviation(s);
}

bool Tokenizer::is_ellipsis(const string& s, int pos) {
    return s[pos] == CharConst::PERIOD &&
    s[pos + 1] == CharConst::PERIOD &&
    s[pos + 2] == CharConst::PERIOD;
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
        
        if (is_terminal_punc(c)) {
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
            if (i + 1 < text.size() && !is_terminal_punc(text[i + 1])) {
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

vector<string *>* Tokenizer::tokenize(const string& text) {
    auto tokens = new vector<string *>();
    
    int prev = 0;
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        
        if (is_whitespace(c)) {
            
            // ignore contiguous chunks of whitespace
            if (prev - i == 0) {
                prev = i + 1;
                continue;
            }
            
            tokens->push_back(new string(text.substr(prev, i - prev)));
            prev = i + 1;
        } else if (is_terminal_punc(c)) {
            
            // append token before terminal punctuation
            if (i - 1 > 0 && !is_terminal_punc(text[i - 1])) {
                tokens->push_back(new string(text.substr(prev, i - prev)));
                prev = i;
            }
            
            // treat consecutive terminal punctations as one tokens
            if (i + 1 < text.size() && !is_terminal_punc(text[i + 1])) {
                tokens->push_back(new string(text.substr(prev, i - prev + 1)));
                prev = i + 1;
            }
        } else if (is_conjunctive(c)) {
            tokens->push_back(new string(text.substr(prev, i - prev)));
            tokens->push_back(new string(1, c));
            
            prev = i + 1;
        } else if (is_apostrophe(c)) {
            int suf_len = eng_apos->is_apostrophe_suffix(text, i + 1);
            
            tokens->push_back(new string(text.substr(prev, i - prev)));
            tokens->push_back(new string(text.substr(i, suf_len + 1)));
            
            prev = i + suf_len + 1;
        }
    }
    
    tokens->push_back(new string(text.substr(prev, text.size() - prev)));
    
    return tokens;
}

