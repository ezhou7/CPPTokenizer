//
//  trie_test.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/14/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "trie_test.hpp"

TrieTest::TrieTest() {
    trie = unique_ptr<Trie>(new Trie());
}

TrieTest::~TrieTest() {
    
}

void TrieTest::basic_test_1() {
    if (trie->get_root() != nullptr)
        cout << "First basic test passed.\n";
}

void TrieTest::basic_test_2() {
    string s = "string";
    trie->insert(s);
    
    if (trie->contains(s) && !trie->contains("string together"))
        cout << "Second basic test passed.\n";
}
