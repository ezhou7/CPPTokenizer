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
    emoticon = unique_ptr<Emoticon>(new Emoticon);
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

string* Tokenizer::substring(const string& s, int start, int end) {
    return StringUtils::substring(s, start, end);
}

vector<string *>* Tokenizer::tokenize(const string& text) {
    auto tokens = new vector<string *>();
    
    int prev = 0;
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        
        if (is_whitespace(c)) {
            // ignore contiguous chunks of whitespace
            if (prev != i)
                tokens->push_back(substring(text, prev, i));
            
            prev = i + 1;
        } else if (int k = is_emoticon(text, i)) {
            cout << "Emoticon working\n";
            // push previous token
            if (prev != i)
                tokens->push_back(substring(text, prev, i));
            
            // treat emoticon as token
            tokens->push_back(new string(text.substr(i, k)));
            
            i = prev = i + k;
        } else if (is_terminal(c)) {
            // check if is abbreviation
            if (is_abbreviation(boost::to_lower_copy(text.substr(prev, i - prev)))) {
                tokens->push_back(substring(text, prev, i + 1));
                prev = i + 1;
                
                continue;
            }
            
            // append token before terminal punctuation
            if (i - 1 > 0 && !is_terminal(text[i - 1])) {
                tokens->push_back(substring(text, prev, i));
                prev = i;
            }
            
            // treat consecutive terminal punctations as one tokens
            if (i + 1 < text.size() && !is_terminal(text[i + 1])) {
                tokens->push_back(substring(text, prev, i + 1));
                prev = i + 1;
            }
        } else if (is_conjunctive(c)) {
            // don't push empty strings
            if (prev != i)
                tokens->push_back(substring(text, prev, i));
            
            // push conjunctive punctuation as token
            tokens->push_back(new string(1, c));
            
            prev = i + 1;
        } else if (is_apostrophe(c)) {
            int suf_len = eng_apos->is_apostrophe_suffix(text, i + 1);
            
            // if there exists an apostrophe suffix, then suf_len > 0
            if (suf_len) {
                if (text[i + 1] == 't' && text[i - 1] == 'n') {
                    if (prev - 1 != i)
                        tokens->push_back(substring(text, prev, i - 1));
                    
                    tokens->push_back(new string(text.substr(i - 1, 3)));
                    
                    prev = i + 2;
                } else {
                    if (prev != i)
                        tokens->push_back(substring(text, prev, i));
                
                    tokens->push_back(new string(text.substr(i, suf_len + 1)));
            
                    prev = i + suf_len + 1;
                }
            } else {
                continue;
            }
        } else if (is_opener(c) || is_encloser(c)) {
            if (prev != i)
                tokens->push_back(substring(text, prev, i));
            
            tokens->push_back(new string(1, c));
            
            prev = i + 1;
        }
    }
    
    tokens->push_back(substring(text, prev, (int) text.size()));
    
    return tokens;
}

/* ------------------- Deprecated ------------------- */

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
