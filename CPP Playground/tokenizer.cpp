//
//  tokenizer.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "tokenizer.hpp"

bool is_whitespace(const string *c) {
    return is_equal(c, &StringConst::SPACE) ||
            is_equal(c, &StringConst::TAB) ||
            is_equal(c, &StringConst::NEWLINE);
}

unique_ptr<vector<string *>> split_whitespace(string *sentence) {
    unique_ptr<vector<string *>> uniq_tokens(new vector<string *>);
    auto *token_primitives = uniq_tokens.get();
    
    int prev = 0;
    for (int i = 0; i < sentence->size(); i++) {
        string s = sentence[i];
        
        if (is_whitespace(&s)) {
            unique_ptr<string> uniq_str(new string(sentence->substr(prev, i)));
            token_primitives->push_back(uniq_str.get());
            
            continue;
        }
    }
    
    return uniq_tokens;
}

string** extract_ellipsis(string *s) {
    for (int i = 0; i < s->size() - 3; i++) {
        bool first = is_equal((const string *) &s[i], &StringConst::PERIOD);
        bool second = !is_equal((const string *) &s[i + 1], &StringConst::PERIOD);
        bool third = !is_equal((const string *) &s[i + 2], &StringConst::PERIOD);
        
        if (first && second && third) {
            if (i != 0) {
                if (i + 3 == s->size() - 1) {
                    string **tokens = new string*[2];
                    
                    tokens[0] = new string(s->substr(0, i));
                    tokens[1] = new string(s->substr(i, i + 3));
                    
                    return tokens;
                } else {
                    string **tokens = new string*[3];
                    
                    tokens[0] = new string(s->substr(0, i));
                    tokens[1] = new string(s->substr(i, i + 3));
                    tokens[2] = new string(s->substr(i + 3, s->size()));
                    
                    return tokens;
                }
            } else {
                string **tokens = new string *[2];
                
                tokens[0] = new string(s->substr(0, 3));
                tokens[1] = new string(s->substr(3, s->size()));
                
                return tokens;
            }
            
        }
    }
    
    string **s_arrayified = new string*[1];
    s_arrayified[0] = (string *)s;
    
    return s_arrayified;
}
