//
//  strutils.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef strutils_hpp
#define strutils_hpp

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>

#include "define.h"

using namespace std;

class StringUtils {
public:
    static bool is_equal(const string& s1, const string& s2);
    
    static str_t substring(const string& s, int start, int end);
    static str_t substring(const string& s, const pair<int, int>& markers);
    
    static str_t join(const vector<str_t>& str_vec, const string& delim);
};

#endif /* strutils_hpp */
