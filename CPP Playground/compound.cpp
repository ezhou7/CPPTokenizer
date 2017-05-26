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
//    auto m_obj = *m_compound;
//    
//    for (auto const& entry : m_obj) {
//        for (int i = 0; i < entry.second->size(); i++) {
//            delete (*entry.second)[i];
//        }
//    }
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
        
        string *s = StringUtils::join(*tokens, StringConst::EMPTY);
        cout << *s << "\n";
        (*m_compound)[*s] = make_unique<vector<str_t>>(*tokens);
        
        delete s;
        
        printf("%p\n", (*m_compound)["youll"].get());
        
        if ((*m_compound)["youll"])
        cout << *(*m_compound)["youll"]->operator[](3) << "\n";
        
        for (int i = 0; i < tokens->size(); i++) {
            delete tokens[0][i];
        }
        
        delete tokens;
    }
    
    in_stream.close();
}


