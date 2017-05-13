//
//  token.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/27/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "token.hpp"

Token::Token(const string& s) {
    setWord(s);
}

Token::~Token() {
    
}

void Token::setWord(const string& s) {
    word = unique_ptr<string>(new string(s));
}

void Token::setStart(int start) {
    this->start = start;
}

void Token::setEnd(int end) {
    this->end = end;
}

const string* Token::getWord() {
    return (const string *) word.get();
}

