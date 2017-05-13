//
//  abbreviation.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/8/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef abbreviation_hpp
#define abbreviation_hpp

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <memory>

#include "dictionary.hpp"
#include "dsutils.hpp"

using namespace std;

class Abbreviation {
private:
    unique_ptr<unordered_set<string>> s_period;
    
    void init(ifstream& in_stream);

public:
    Abbreviation();
    Abbreviation(ifstream& in_stream);
    ~Abbreviation();
    
    bool is_abbreviation(const string& s);
};

#endif /* abbreviation_hpp */
