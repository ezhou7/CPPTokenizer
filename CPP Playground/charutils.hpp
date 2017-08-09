//
//  charutils.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef charutils_hpp
#define charutils_hpp

#include <stdio.h>

#include "charconst.hpp"

class CharUtils {
public:
    static bool is_whitespace(char const& c);
    static bool is_terminal(const char& c);
    static bool is_conjunctive(const char& c);
    static bool is_apostrophe(const char& c);
    static bool is_opener(const char& c);
    static bool is_encloser(const char& c);
};

#endif /* charutils_hpp */
