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
#include <boost/algorithm/string/case_conv.hpp>

#include "define.h"

#include "abbreviation.hpp"
#include "apostrophe.hpp"
#include "emoticon.hpp"

#include "char_const.hpp"
#include "string_const.hpp"

#include "charutils.hpp"
#include "strutils.hpp"

using namespace std;

class Tokenizer {
private:
    uptr_t<Abbreviation> abbrev;
    uptr_t<EnglishApostrophe> eng_apos;
    uptr_t<Emoticon> emoticon;
    
    bool is_whitespace(const char& c);
    bool is_terminal(const char& c);
    
    bool is_conjunctive(const char& c);
    bool is_apostrophe(const char& c);
    
    bool is_opener(const char& c);
    bool is_encloser(const char& c);
    
    bool is_abbreviation(const string& s);
    bool is_ellipsis(const string& s, int pos);
    
    bool is_emoticon(const string& s);
    int is_emoticon(const string& s, const int pos);
    
    str_t substring(const string& s, int start, int end);
    void add_token(vector<str_t> *tokens, const string& s, int start, int end);
    
public:
    Tokenizer();
    ~Tokenizer();
    
    vector<str_t>* tokenize(const string& text);
    
    vector<str_t>* split_whitespace(const string& sentence) __attribute__ ((deprecated));
    vector<str_t>* segmentize(const string& text) __attribute__((deprecated));
};

#endif /* tokenizer_hpp */
