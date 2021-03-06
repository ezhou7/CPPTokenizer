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
#include "compound_test.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
//    if (argc < 2) {
//        cout << "No arugments presented.\n";
//        return 0;
//    }
//    
//    // TODO: complete ArgumentParser
//    
//    char c = argv[1][1];
//    
//    switch (c) {
//        case 'h':
//            cout << "Help section:\n";
//            break;
//            
//        default:
//            cout << "Arguments not recognized.\n";
//            cout << "Run with argument \"-h\" for help.\n";
//            break;
//    }
    
//    string s = "Some people are careless.";
//
//    unique_ptr<basic_regex<char>> uniq_re(new basic_regex<char>("\\w+"));
//    bool match = regex_search(s, *(basic_regex<char> *) uniq_re.get());
//    
//    cout << ((match) ? "Match" : "No match") << endl;
    
    TokenizerTest tokenizer_test;
    tokenizer_test.TerminalTest();
    tokenizer_test.ApostropheTest();
    tokenizer_test.HyphenTest();
//    tokenizer_test.ParenthesesTest();
//    tokenizer_test.CompoundTest();
//    tokenizer_test.CurrencyTest();
    
//    tokenizer_test.SimpleTest();
//    tokenizer_test.ModerateTest();
//    tokenizer_test.AdvancedTest();
    
//    TrieTest trie_test;
//    
//    trie_test.basic_test_1();
//    trie_test.basic_test_2();
    
//    CompoundTest compound_test;
//    compound_test.test_compound_init();
    
    return 0;
}
