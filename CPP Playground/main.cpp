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

#include "test.hpp"
#include "tokenizer_test.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    string s = "Some people are careless.";

    unique_ptr<basic_regex<char>> uniq_re(new basic_regex<char>("\\w+"));
    bool match = regex_search(s, *(basic_regex<char> *) uniq_re.get());
    
    cout << ((match) ? "Match" : "No match") << endl;
    
    test_all();
    
    TokenizerTest tokenizer_test;
    
    tokenizer_test.simple_test();
    tokenizer_test.moderate_test();
    tokenizer_test.advanced_test();
    
    return 0;
}
