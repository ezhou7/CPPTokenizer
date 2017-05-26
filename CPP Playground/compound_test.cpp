//
//  compound_test.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/20/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "compound_test.hpp"

CompoundTest::CompoundTest() {
    
}

CompoundTest::~CompoundTest() {
    
}

void CompoundTest::test_compound_init() {
    compound = unique_ptr<Compound>(new Compound());
}
