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
            test_str = "This is an advanced tokenization test.  Is it too advanced?I think so,but...shouldn't be, because I'm not sure why.  \"But here are some days of the week:Mon., Tues., Wednesday, Thurs.\", said Ms. O'Donnell. >:) a";
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

void TokenizerTest::SimpleTest() {
    test(Complexity::simple);
}

void TokenizerTest::ModerateTest() {
    test(Complexity::moderate);
}

void TokenizerTest::AdvancedTest() {
    test(Complexity::advanced);
}

void TokenizerTest::CompoundTest() {
    string test_type = "compound";
    string test_str = "Compounds shouldnt be a problem.shouldnt>:)Dont do it.";
    test(test_type, test_str);
}

void TokenizerTest::CurrencyTest() {
    string test_type = "currency";
    string test_str = "This is a form of currency:usd. I have $1.";
    test(test_type, test_str);
}

void TokenizerTest::TerminalTest() {
    string test_type = "terminal";
    string test_str = "This is a test of tokenizing terminals... terminals are periods, exclamation marks, question marks like so \"???!!!\". These mark the end of a clause.";
    test(test_type, test_str);
}

void TokenizerTest::ApostropheTest() {
    string test_type = "apostrophe";
    string test_str = "This is a test of tokenizing apostrophes: \"You're a great person. I'm so happy to have you on the team.  But you shouldn't tell them about it yet.\"";
    test(test_type, test_str);
}

void TokenizerTest::ParenthesesTest() {
    string test_type = "parentheses";
    string test_str = "This is a test of tokenizing parentheses (pair of parentheses)(((((set of parentheses))))).";
    test(test_type, test_str);
}
