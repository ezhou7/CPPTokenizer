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

#include <string>

using namespace std;

class StringUtils {
public:
    static bool is_equal(const string& s1, const string& s2);
    static string* substring(const string& s, int start, int end);
    static string* substring(const string& s, const pair<int, int>& markers);
};

#endif /* strutils_hpp */
