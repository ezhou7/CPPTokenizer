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
#include <iterator>
#include <utility>
#include <cctype>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include "define.h"

#include "token.hpp"
#include "abbreviation.hpp"
#include "apostrophe.hpp"
#include "emoticon.hpp"
#include "compound.hpp"
#include "currency.hpp"

#include "charconst.hpp"
#include "strconst.hpp"

#include "charutils.hpp"
#include "strutils.hpp"

using namespace std;

class Tokenizer {
private:
    uptr_t<Abbreviation> abbrev;
    uptr_t<EnglishApostrophe> eng_apos;
    uptr_t<Emoticon> emoticon;
    uptr_t<Compound> compound;
    uptr_t<Currency> currency;
    
    bool is_whitespace(const char& c);
    bool is_terminal(const char& c);
    
    bool is_conjunctive(const char& c);
    bool is_apostrophe(const char& c);
    
    bool is_opener(const char& c);
    bool is_encloser(const char& c);
    
    bool is_abbreviation(const string& s);
    bool is_ellipsis(const string& s, int pos);
    
    int is_emoticon(const string& s, const int pos);
    
    bool is_compound(const string& s);
    
    int is_currency(const string& s, int pos);
    int is_dollar(const string& s, int pos);
    
    void add_tokens(up_tvec_t& tokens, up_tvec_t& extension);
    
    up_tvec_t TokenizeByWhitespace(const string& text, int prev, int curr);
    up_tvec_t TokenizePreviousWord(const string& text, int start, int end);
    up_tvec_t TokenizeEmoticon(const string& text, int prev, int curr);
    up_tvec_t TokenizeByTerminal(const string& text, int prev, int curr);
    up_tvec_t TokenizeConjunctive(const string& text, int prev, int curr);
    up_tvec_t TokenizeByApostrophe(const string& text, int prev, int curr);
    up_tvec_t TokenizeParentheses(const string& text, int prev, int curr);
    up_tvec_t TokenizeCurrency(const string& text, int prev, int curr);
    up_tvec_t TokenizeCurrencyDollars(const string& text, int prev, int curr);
    up_tvec_t TokenizeCurrencyAux(const string& text, int prev, int curr, bool isDollarCurrency);
    
public:
    Tokenizer();
    ~Tokenizer();
    
    up_tvec_t tokenize(const string& text);
};

#endif /* tokenizer_hpp */
