//
//  string_const.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef string_const_hpp
#define string_const_hpp

#include <stdio.h>

#include <string>

using namespace std;

class StringConst {
public:
    // empty
    static const string EMPTY;
    
    // whitespace
    static const string SPACE;
    static const string TAB;
    static const string NEWLINE;
    
    // punctuation
    static const string ELLIPSIS;
    static const string PERIOD;
    static const string COMMA;
    static const string COLON;
    static const string SEMICOLON;
    
    // hyphenation
    static const string DASH;
    static const string UNDERSCORE;
    
    // enclosure
    static const string LEFT_PARENS;
    static const string RIGHT_PARENS;
    
    static const string LEFT_BRACKET;
    static const string RIGHT_BRACKET;
    
    static const string LEFT_BRACE;
    static const string RIGHT_BRACE;
    
    static const string LESS_THAN;
    static const string GREATER_THAN;
};

#endif /* string_const_hpp */
