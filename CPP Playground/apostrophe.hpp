//
//  apostrophe.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef apostrophe_hpp
#define apostrophe_hpp

#include <stdio.h>

#include <string>
#include <vector>

#include "define.h"
#include "char_const.hpp"

using namespace std;

class EnglishApostrophe {
private:
    const int len = 9;
    const string APOSTROPHE_SUFFIXES[9] = {"d", "m", "s", "t", "z", "ll", "nt", "re", "ve"};
    
    bool is_suffix(const string& s, int pos);

public:
    EnglishApostrophe();
    ~EnglishApostrophe();
    
    int is_apostrophe_suffix(const string& s, int pos);
};

#endif /* apostrophe_hpp */
