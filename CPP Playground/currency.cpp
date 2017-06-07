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
    s_currency = uptr_t<Trie>(create_trie(in_currency));
    s_dollar = uptr_t<Trie>(create_trie(in_dollar));
}

bool Currency::is_currency(const string& lower) {
    return s_currency->contains(lower);
}

bool Currency::is_dollar(const string& lower) {
    return s_dollar->contains(lower);
}

int Currency::is_currency(const string& lower, int pos) {
    return s_currency->contains(lower, pos);
}

int Currency::is_dollar(const string& lower, int pos) {
    return s_dollar->contains(lower, pos);
}
