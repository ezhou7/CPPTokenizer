//
//  tokenizer.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef tokenizer_hpp
#define tokenizer_hpp

#include <stdio.h>

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <cctype>

#include <boost/algorithm/string.hpp>

#include "abbreviation.hpp"
#include "apostrophe.hpp"

#include "char_const.hpp"
#include "strutils.hpp"

using namespace std;

class Tokenizer {
private:
    unique_ptr<Abbreviation> abbrev;
    unique_ptr<EnglishApostrophe> eng_apos;
    
    bool is_whitespace(const char& c);
    bool is_terminal_punc(const char& c);
    bool is_conjunctive(const char& c);
    bool is_apostrophe(const char& c);
    
    bool is_abbreviation(const string& s, int pos);
    bool is_ellipsis(const string& s, int pos);
    
public:
    Tokenizer();
    ~Tokenizer();
    
    vector<string *>* split_whitespace(const string& sentence);
    vector<string *>* segmentize(const string& text);
    vector<string *>* tokenize(const string& text);
};

#endif /* tokenizer_hpp */
