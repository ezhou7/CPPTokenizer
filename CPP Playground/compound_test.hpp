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

#include "compound.hpp"

class CompoundTest {
private:
    Compound compound;
    
    bool exists(const string& s);
    
public:
    CompoundTest();
    ~CompoundTest();
    
    void test();
};

#endif /* compound_test_hpp */
