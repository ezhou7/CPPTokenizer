//
//  main.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include <iostream>
#include <string>
#include <regex>
#include <memory>

#include "tokenizer_test.hpp"
#include "trie_test.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
//    string s = "Some people are careless.";
//
//    unique_ptr<basic_regex<char>> uniq_re(new basic_regex<char>("\\w+"));
//    bool match = regex_search(s, *(basic_regex<char> *) uniq_re.get());
//    
//    cout << ((match) ? "Match" : "No match") << endl;
    
    TokenizerTest tokenizer_test;
    
    tokenizer_test.simple_test();
    tokenizer_test.moderate_test();
    tokenizer_test.advanced_test();
    
//    TrieTest trie_test;
//    
//    trie_test.basic_test_1();
//    trie_test.basic_test_2();
    
    return 0;
}
