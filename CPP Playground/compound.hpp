//
//  compound.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/20/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef compound_hpp
#define compound_hpp

#include <stdio.h>

#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <utility>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#include "define.h"

#include "token.hpp"
#include "dictionary.hpp"

#include "string_const.hpp"
#include "strutils.hpp"

using namespace std;

class Compound {
private:
    uptr_t<hmap_t<string, uptr_t<vector<str_t>>>> m_compound;
    
    void init(ifstream& in_stream);
    
public:
    Compound();
    Compound(ifstream& in_stream);
    ~Compound();
    
    bool is_compound(const string& s);
    vector<str_t>* get_words(const string& s);
    
    up_tvec_t tokenize(const string& s, int spos, int epos);
};

#endif /* compound_hpp */
