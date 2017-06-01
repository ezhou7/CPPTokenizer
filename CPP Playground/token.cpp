//
//  token.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/27/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "token.hpp"

Token::Token(const string& s, int start, int end) {
    setWord(s);
    setStart(start);
    setEnd(end);
}

Token::~Token() {
    
}

void Token::setWord(const string& s) {
    word = up_str_t(new string(s));
}

void Token::setStart(int start) {
    this->start = start;
}

void Token::setEnd(int end) {
    this->end = end;
}

const str_t Token::getWord() {
    return (const str_t) word.get();
}

