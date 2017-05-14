//
//  apostrophe.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "apostrophe.hpp"

EnglishApostrophe::EnglishApostrophe() {
    
}

EnglishApostrophe::~EnglishApostrophe() {
    
}

/*!
    check if reached end of word or end of string

    \param s entire string being tokenized
    \param pos position of last char in suffix w.r.t. to string "s"
 */
bool EnglishApostrophe::is_suffix(const string& s, int pos) {
    return (pos + 1 >= s.size() || !isalpha(s[pos + 1])) ? true : false;
}

/*!
    check if apostrophe suffix exists

    \param s entire string being tokenized
    \param pos position of first char after apostrophe, NOT position of apostrophe itself
 */
int EnglishApostrophe::is_apostrophe_suffix(const string& s, int pos) {
    for (int i = 0; i < len; i++) {
        auto suf = APOSTROPHE_SUFFIXES[i];
        
        switch (suf.size()) {
            case 1:
                // can safely return b/c all apos. suffixes begin w/ different chars.
                if (s[pos] == suf[0] && is_suffix(s, pos))
                    return 1;
                break;
            case 2:
                // see comment for "case 1"
                if (s[pos] == suf[0] && s[pos + 1] == suf[1] && is_suffix(s, pos + 1))
                    return 2;
                break;
                
            default:
                break;
        }
    }
    
    return 0;
}
