//
//  char_const.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/7/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef char_const_hpp
#define char_const_hpp

#include <stdio.h>

class CharConst {
public:
    // whitespace
    static const char SPACE;
    static const char TAB;
    static const char NEWLINE;
    
    // punctuation - terminal
    static const char PERIOD;
    static const char EXCLAMATION;
    static const char QUESTION;
    
    // punctuation - conjunctive
    static const char COMMA;
    static const char COLON;
    static const char SEMICOLON;
    
    // hyphenation
    static const char DASH;
    static const char UNDERSCORE;
    
    // concatenation
    static const char APOSTROPHE;
    
    // enclosure
    static const char LEFT_PARENS;
    static const char RIGHT_PARENS;
    
    static const char LEFT_BRACKET;
    static const char RIGHT_BRACKET;
    
    static const char LEFT_BRACE;
    static const char RIGHT_BRACE;
    
    static const char LESS_THAN;
    static const char GREATER_THAN;
    
    static const char DOUBLE_QUOTE;
    static const char SINGLE_QUOTE;
};

#endif /* char_const_hpp */
