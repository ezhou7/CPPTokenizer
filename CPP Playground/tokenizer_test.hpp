//
//  tokenizer_test.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef tokenizer_test_hpp
#define tokenizer_test_hpp

#include <stdio.h>

#include "tokenizer.hpp"

enum class Complexity {
    simple,
    moderate,
    advanced
};

enum class Specialized {
    abbreviation,
    emoticon,
    hyphen,
    currency
};

class TokenizerTest {
private:
    Tokenizer *tokenizer;
    
    void test(Complexity level);
    void test(const string& test_type, const string& test_str);
    
public:
    TokenizerTest();
    ~TokenizerTest();
    
    void SimpleTest();
    void ModerateTest();
    void AdvancedTest();
    
    void CompoundTest();
    void CurrencyTest();
    void TerminalTest();
    void ApostropheTest();
    void ParenthesesTest();
};

#endif /* tokenizer_test_hpp */
