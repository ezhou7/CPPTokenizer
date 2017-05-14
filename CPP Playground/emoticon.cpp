//
//  emoticon.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "emoticon.hpp"

Emoticon::Emoticon() {
    const string fpath = Dictionary::ROOT + "emoticons.txt";
    
    ifstream in_stream(fpath);
    init(in_stream);
}

Emoticon::Emoticon(ifstream& in_stream) {
    init(in_stream);
}

Emoticon::~Emoticon() {
    
}

void Emoticon::init(ifstream& in_stream) {
    t_emoticon = unique_ptr<Trie>(create_trie(in_stream));
}

bool Emoticon::is_emoticon(const string& s) {
    return t_emoticon->contains(s);
}

bool Emoticon::is_emoticon(const string& s, int pos) {
    return t_emoticon->contains(s, pos);
}
