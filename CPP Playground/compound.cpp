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
        
        auto str_tokens = new vector<str_t>();
        
        for (int i = 0; i < fields.size(); i++) {
            str_tokens->push_back(new string(fields[i]));
        }
        
        str_t s = StringUtils::join(*str_tokens, StringConst::EMPTY);
        (*m_compound)[*s] = make_unique<vector<str_t>>(*str_tokens);
        
        delete s;
    }
    
    in_stream.close();
}

bool Compound::is_compound(const string& s) {
    return m_compound->count(s);
}

vector<str_t>* Compound::get_words(const string& s) {
    return m_compound.get()[0][s].get();
}

up_tvec_t Compound::tokenize(const string& s, int spos, int epos) {
    auto tokens = up_tvec_t(new vector<up_token_t>());
    
    string lowered = boost::to_lower_copy(s);
    if (is_compound(lowered)) {
        auto split_words = get_words(lowered);
        
        int start = spos;
        for (int i = 0; i < split_words->size(); i++) {
            auto word = *(*split_words)[i];
            int end = start + (int) word.size();
            token_t token = new Token(word, start, end);
            
            tokens->push_back(up_token_t(token));
            start = end;
        }
    } else {
        tokens->push_back(up_token_t(new Token(s, spos, epos)));
    }
    
    return tokens;
}


