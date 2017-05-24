//
//  compound.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/20/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "compound.hpp"

Compound::Compound() {
    const string fpath = Dictionary::ROOT + "english-compounds.txt";
    ifstream in_stream(fpath);
    
    init(in_stream);
}

Compound::Compound(ifstream& in_stream) {
    init(in_stream);
}

Compound::~Compound() {
    auto m_obj = *m_compound;
    
    for (auto const& entry : m_obj) {
        for (int i = 0; i < entry.second->size(); i++) {
            delete (*entry.second)[i];
        }
    }
}

void Compound::init(ifstream& in_stream) {
    m_compound = new unordered_map<string, unique_ptr<vector<string *>>>();
    
    string line;
    while (getline(in_stream, line)) {
        vector<string> fields;
        boost::split(fields, line, boost::is_any_of(StringConst::SPACE));
        
        auto tokens = unique_ptr<vector<string *>>(new vector<string *>());
        
        for (int i = 0; i < fields.size(); i++) {
            tokens->push_back(new string(fields[i]));
        }
        
        string *s = boost::join(*tokens.get(), StringConst::EMPTY);
        m_compound->insert(make_pair(*s, tokens));
        
        delete s;
    }
    
    in_stream.close();
}
