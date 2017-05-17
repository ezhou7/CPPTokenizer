//
//  emoticon.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef emoticon_hpp
#define emoticon_hpp

#include <stdio.h>

#include <fstream>
#include <memory>
#include <unordered_set>

#include "trie.hpp"
#include "dictionary.hpp"
#include "dsutils.hpp"

using namespace std;

class Emoticon {
private:
    unique_ptr<Trie> t_emoticon;
    
    void init(ifstream& in_stream);

public:
    Emoticon();
    Emoticon(ifstream& in_stream);
    ~Emoticon();
    
    bool is_emoticon(const string& s);
    int is_emoticon(const string& s, int pos);
};

#endif /* emoticon_hpp */
