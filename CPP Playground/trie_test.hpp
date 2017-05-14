//
//  trie_test.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/14/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef trie_test_hpp
#define trie_test_hpp

#include <stdio.h>

#include "trie.hpp"

class TrieTest {
private:
    unique_ptr<Trie> trie;
    
public:
    TrieTest();
    ~TrieTest();
    
    void basic_test_1();
    void basic_test_2();
};

#endif /* trie_test_hpp */
