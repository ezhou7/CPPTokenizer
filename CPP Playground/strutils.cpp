//
//  strutils.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "strutils.hpp"

bool StringUtils::is_equal(const string& s1, const string& s2) {
    return s1.compare(s2) == 0;
}

str_t StringUtils::substring(const string& s, int start, int end) {
    return new string(s.substr(start, end - start));
}

str_t StringUtils::substring(const string& s, const pair<int, int>& markers) {
    return substring(s, markers.first, markers.second);
}

str_t StringUtils::join(const vector<str_t>& str_vec, const string& delim) {
    int sz = 0;
    for (int i = 0; i < str_vec.size(); i++) {
        sz += str_vec[i]->size();
    }
    
    char char_vec[sz + 1];
    
    int count = 0;
    for (int i = 0; i < str_vec.size(); i++) {
        string s = *str_vec[i];
        for (int j = 0; j < s.size(); j++) {
            char_vec[count++] = s[j];
        }
    }
    
    char_vec[count] = '\0';
    
    return new string(char_vec);
}
