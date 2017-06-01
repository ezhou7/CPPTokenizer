//
//  currency.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/28/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "currency.hpp"

Currency::Currency() {
    string fpath_c = Dictionary::ROOT + "currency.txt";
    string fpath_d = Dictionary::ROOT + "currency-dollar.txt";
    
    ifstream in_currency(fpath_c);
    ifstream in_dollar(fpath_d);
    
    init(in_currency, in_dollar);
}

Currency::Currency(ifstream& in_currency, ifstream& in_dollar) {
    init(in_currency, in_dollar);
}

Currency::~Currency() {
    
}

void Currency::init(ifstream& in_currency, ifstream& in_dollar) {
    s_currency = uptr_t<hset_t<string>>(create_strset(in_currency));
    s_dollar = uptr_t<hset_t<string>>(create_strset(in_dollar));
}

bool Currency::is_currency(const string& lower) {
    return s_currency->count(lower);
}

bool Currency::is_dollar(const string& lower) {
    return s_dollar->count(lower);
}
