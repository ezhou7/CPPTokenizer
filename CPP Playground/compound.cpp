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
    for (auto const& entry : *m_compound.get()) {
        auto tokens = entry.second.get()[0];
        
        for (int i = 0; i < tokens.size(); i++) {
            delete tokens[i];
        }
    }
}

void Compound::init(ifstream& in_stream) {
    m_compound = uptr_t<hmap_t<string, uptr_t<vector<str_t>>>>(new hmap_t<string, uptr_t<vector<str_t>>>());
    
    string line;
    while (getline(in_stream, line)) {
        vector<string> fields;
        boost::split(fields, line, boost::is_any_of(StringConst::SPACE));
        
        auto tokens = new vector<str_t>();
        
        for (int i = 0; i < fields.size(); i++) {
            tokens->push_back(new string(fields[i]));
        }
        
        str_t s = StringUtils::join(*tokens, StringConst::EMPTY);
        (*m_compound)[*s] = make_unique<vector<str_t>>(*tokens);
        
        delete s;
    }
    
    in_stream.close();
}

bool Compound::is_compound(const string& s) {
    return m_compound->count(s);
}

vector<str_t>* Compound::get_tokens(const string& s) {
    return m_compound.get()[0][s].get();
}


