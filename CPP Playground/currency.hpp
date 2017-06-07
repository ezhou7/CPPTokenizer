//
//  currency.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/28/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef currency_hpp
#define currency_hpp

#include <stdio.h>

#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

#include "define.h"

#include "token.hpp"
#include "dictionary.hpp"
#include "trie.hpp"

#include "dsutils.hpp"

using namespace std;

class Currency {
private:
    uptr_t<Trie> s_currency;
    uptr_t<Trie> s_dollar;
    
    void init(ifstream& in_currency, ifstream& in_dollar);

public:
    Currency();
    Currency(ifstream& in_currency, ifstream& in_dollar);
    ~Currency();
    
    bool is_currency(const string& lower);
    bool is_dollar(const string& lower);
    
    int is_currency(const string& lower, int pos);
    int is_dollar(const string& lower, int pos);
};

#endif /* currency_hpp */
