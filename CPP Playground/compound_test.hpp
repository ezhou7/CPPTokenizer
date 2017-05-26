//
//  compound_test.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/20/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef compound_test_hpp
#define compound_test_hpp

#include <stdio.h>

#include <memory>

#include "compound.hpp"

using namespace std;

class CompoundTest {
private:
    unique_ptr<Compound> compound;
    
public:
    CompoundTest();
    ~CompoundTest();
    
    void test_compound_init();
};

#endif /* compound_test_hpp */
