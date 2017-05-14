//
//  charutils.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "charutils.hpp"

bool CharUtils::is_whitespace(const char& c) {
    return c == CharConst::SPACE || c == CharConst::TAB || c == CharConst::NEWLINE;
}

bool CharUtils::is_terminal(const char& c) {
    return c == CharConst::PERIOD || c == CharConst::EXCLAMATION || c == CharConst::QUESTION;
}

bool CharUtils::is_conjunctive(const char& c) {
    return c == CharConst::COMMA || c == CharConst::COLON || c == CharConst::SEMICOLON;
}

bool CharUtils::is_apostrophe(const char& c) {
    return c == CharConst::APOSTROPHE;
}

bool CharUtils::is_opener(const char& c) {
    return c == CharConst::DOUBLE_QUOTE ||
        c == CharConst::LEFT_PARENS ||
        c == CharConst::LEFT_BRACKET ||
        c == CharConst::LEFT_BRACE;
}

bool CharUtils::is_encloser(const char& c) {
    return c == CharConst::DOUBLE_QUOTE ||
        c == CharConst::RIGHT_PARENS ||
        c == CharConst::RIGHT_BRACKET ||
        c == CharConst::RIGHT_BRACE;
}
