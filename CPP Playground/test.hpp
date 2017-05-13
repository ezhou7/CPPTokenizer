//
//  test.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/7/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>

#include <iostream>
#include <cassert>
#include <string>

#include "token.hpp"
#include "tokenizer.hpp"
#include "abbreviation.hpp"
#include "strutils.hpp"

using namespace std;

void test_all();

// object construction tests
void token_test();
void abbreviation_test();

// tokenization tests
void split_whitespace_test();
void split_sentences_test();

#endif /* test_hpp */
