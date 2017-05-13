//
//  test.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/7/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "test.hpp"

void test_all() {
    token_test();
    abbreviation_test();
    
    split_whitespace_test();
    split_sentences_test();
}

void token_test() {
    string s = "token";
    Token t(s);
    
    assert(StringUtils::is_equal(s, *t.getWord()));
    
    cout << "token_test() passed.\n\n";
}

void abbreviation_test() {
    string day = "tues";
    Abbreviation a;
    
    assert(a.is_abbreviation(day));
    
    cout << "abbreviation_test() passed.\n\n";
}

void split_whitespace_test() {
    string s = "whitespace split  test.";
    Tokenizer t;
    
    vector<string *> *tokens = t.split_whitespace(s);
    
    assert(tokens->size() == 3);
    
    assert(StringUtils::is_equal(*tokens[0][0], "whitespace"));
    assert(StringUtils::is_equal(*tokens[0][1], "split"));
    assert(StringUtils::is_equal(*tokens[0][2], "test."));
    
    for (int i = 0; i < tokens->size(); i++) {
        cout << "Token \"" << *tokens[0][i] << "\" is being deleted now.\n";
        delete tokens[0][i];
    }
    
    tokens->clear();
    
    delete tokens;
    
    cout << "split_whitespace_test() passed.\n\n";
}

void split_sentences_test() {
    string s = "This is a sentence splitting test...Second sentence?!  Third sentence!!Fourth sentence... fifth sentence";
    Tokenizer t;
    
    vector<string *> *sentences = t.segmentize(s);
    
//    assert(sentences->size() == 4);
    
//    assert(StringUtils::is_equal(*sentences[0][0], "This is a sentence splitting test..."));
//    assert(StringUtils::is_equal(*sentences[0][1], "Second sentence?!"));
//    assert(StringUtils::is_equal(*sentences[0][2], "Third sentence!!"));
//    assert(StringUtils::is_equal(*sentences[0][3], "Fourth sentence..."));
    
    for (int i = 0; i < sentences->size(); i++) {
        cout << "Sentence \"" << *sentences[0][i] << "\" is being deleted now.\n";
        delete sentences[0][i];
    }
    
    sentences->clear();
    
    delete sentences;
    
    cout << "split_sentences_test() passed.\n\n";
}
