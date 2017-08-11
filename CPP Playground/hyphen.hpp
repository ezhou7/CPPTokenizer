//
//  hyphen.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 8/9/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef hyphen_hpp
#define hyphen_hpp

#include <stdio.h>

#include <fstream>
#include <string>
#include <memory>
#include <unordered_set>

#include "define.h"

#include "trie.hpp"
#include "dictionary.hpp"
#include "dsutils.hpp"

using namespace std;

class EnglishHyphen {
private:
    uptr_t<hset_t<string>> prefixSet;
    uptr_t<hset_t<string>> suffixSet;
    
    void init();
    
public:
    EnglishHyphen();
    ~EnglishHyphen();
    
    bool isPrefix(const string& lower);
    bool isSuffix(const string& lower);
};

#endif /* hyphen_hpp */
