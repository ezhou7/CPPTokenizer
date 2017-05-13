//
//  dsutils.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/8/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "dsutils.hpp"

unordered_set<string>* create_strset(ifstream& in_stream) {
    if (!in_stream.is_open()) {
        cout << "File is invalid or has been closed already.\n";
        return nullptr;
    }
    
    auto str_set = new unordered_set<string>();
    
    string line;
    while (getline(in_stream, line)) {
        str_set->insert(line);
    }
    
    in_stream.close();
    
    return str_set;
}
