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
#include <unordered_set>

#include "define.h"

#include "dictionary.hpp"
#include "dsutils.hpp"

using namespace std;

class Currency {
private:
    uptr_t<hset_t<string>> s_currency;
    uptr_t<hset_t<string>> s_dollar;
    
    void init(ifstream& in_currency, ifstream& in_dollar);

public:
    Currency();
    Currency(ifstream& in_currency, ifstream& in_dollar);
    ~Currency();
    
    bool is_currency(const string& lower);
    bool is_dollar(const string& lower);
};

#endif /* currency_hpp */
