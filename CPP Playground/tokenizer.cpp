//
//  tokenizer.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "tokenizer.hpp"

bool is_whitespace(string c) {
    return c == StringConst::SPACE || c == StringConst::TAB || c == StringConst::NEWLINE;
}

unique_ptr<vector<string *>> split_whitespace(string *sentence) {
    unique_ptr<vector<string *>> uniq_tokens(new vector<string *>);
    vector<string *> *token_primitives = uniq_tokens.get();
    
    int prev = 0;
    for (int i = 0; i < sentence->size(); i++) {
        string s = sentence[i];
        
        if (is_whitespace(s)) {
            unique_ptr<string> uniq_str(new string(sentence->substr(prev, i)));
            token_primitives->push_back(uniq_str.get());
            
            continue;
        }
    }
    
    return uniq_tokens;
}

bool extract_ellipsis(string token) {
    return false;
}
