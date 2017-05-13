//
//  abbreviation.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/8/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "abbreviation.hpp"

Abbreviation::Abbreviation() {
    const string fpath = Dictionary::ROOT + "abbreviation-period.txt";
    
    ifstream in_stream(fpath);
    init(in_stream);
}

Abbreviation::Abbreviation(ifstream& in_stream) {
    init(in_stream);
}

Abbreviation::~Abbreviation() {
    
}

void Abbreviation::init(ifstream& in_stream) {
    s_period = make_unique<unordered_set<string>>(*create_strset(in_stream));
}

bool Abbreviation::is_abbreviation(const string& lower) {
    return s_period->count(lower);
}
