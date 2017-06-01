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

void test_all() __attribute__ ((deprecated));

// object construction tests
void token_test() __attribute__ ((deprecated));
void abbreviation_test() __attribute__ ((deprecated));

// tokenization tests
void split_whitespace_test() __attribute__ ((deprecated));
void split_sentences_test() __attribute__ ((deprecated));

#endif /* test_hpp */
