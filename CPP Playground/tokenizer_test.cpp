//
//  tokenizer_test.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "tokenizer_test.hpp"

TokenizerTest::TokenizerTest() {
    tokenizer = new Tokenizer();
}

TokenizerTest::~TokenizerTest() {
    delete tokenizer;
}

void TokenizerTest::test(Complexity level) {
    string test_type = "";
    string test_str = "";
    
    switch (level) {
        case Complexity::simple:
            test_type = "simple";
            test_str = "This is a simple tokenization test";
            break;
        case Complexity::moderate:
            test_type = "moderate";
            test_str = "This is a moderate tokenization test.  A moderate test???Wait a second...Uhhh, I'm not sure what to do... Maybe I've done goofed.";
            break;
        case Complexity::advanced:
            test_type = "advanced";
            test_str = "This is an advanced tokenization test.  Is it too advanced?I think so,but...shouldn't be, because I'm not sure why.  \"But here are some days of the week:Mon., Tues., Wednesday, Thurs.\", said Ms. O'Donnell. >:) ";
            break;
        
        default:
            cout << "Unrecognized test type.\n\n";
            return;
    }
    
    test(test_type, test_str);
}

void TokenizerTest::test(const string& test_type, const string& test_str) {
    cout << "Beginning " << test_type << " tokenizer test...\n\n";
    
    auto tokens = tokenizer->tokenize(test_str);
    
    cout << "String for tokenization: " << test_str << "\n\n";
    
    cout << "Tokens:\n";
    for (int i = 0; i < tokens->size(); i++) {
        auto str_token = tokens.get()[0][i]->getWord();
        
        cout << *str_token << "\n";
    }
    
    cout << "Ending " << test_type << " tokenizer test.\n\n";
}

void TokenizerTest::simple_test() {
    test(Complexity::simple);
}

void TokenizerTest::moderate_test() {
    test(Complexity::moderate);
}

void TokenizerTest::advanced_test() {
    test(Complexity::advanced);
}

void TokenizerTest::compound_test() {
    string test_type = "compound";
    string test_str = "Compounds shouldnt be a problem.shouldnt>:)";
    test(test_type, test_str);
}

