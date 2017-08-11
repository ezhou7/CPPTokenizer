//
//  hyphen.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 8/9/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "hyphen.hpp"

EnglishHyphen::EnglishHyphen() {
    init();
}

EnglishHyphen::~EnglishHyphen() {
    
}

void EnglishHyphen::init() {
    const string prefixPath = Dictionary::ROOT + "english-hyphen-prefix.txt";
    const string suffixPath = Dictionary::ROOT + "english-hyphen-suffix.txt";
    
    ifstream prefixStream(prefixPath);
    prefixSet = uptr_t<hset_t<string>>(create_strset(prefixStream));
    
    ifstream suffixStream(suffixPath);
    suffixSet = uptr_t<hset_t<string>>(create_strset(suffixStream));
}

bool EnglishHyphen::isPrefix(const string& lower) {
    return prefixSet->count(lower);
}

bool EnglishHyphen::isSuffix(const string& lower) {
    return suffixSet->count(lower);
}
