//
//  compound.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/20/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef compound_hpp
#define compound_hpp

#include <stdio.h>

#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#include "dictionary.hpp"

#include "string_const.hpp"
#include "strutils.hpp"

using namespace std;

class Compound {
private:
    unordered_map<string, unique_ptr<vector<string *>>> *m_compound;
    
    void init(ifstream& in_stream);
    
public:
    Compound();
    Compound(ifstream& in_stream);
    ~Compound();
};

#endif /* compound_hpp */
