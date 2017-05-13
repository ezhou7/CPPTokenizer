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

string* StringUtils::substring(const string& s, int start, int end) {
    return new string(s.substr(start, end - start));
}

string* StringUtils::substring(const string& s, const pair<int, int>& markers) {
    return substring(s, markers.first, markers.second);
}
