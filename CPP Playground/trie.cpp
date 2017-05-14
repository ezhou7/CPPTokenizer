//
//  trie.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "trie.hpp"

TrieNode::TrieNode() {
    this->c = 0;
    this->parent = nullptr;
}

TrieNode::TrieNode(const char& c, TrieNode& p) {
    this->c = c;
    this->parent = &p;
    
    p.children[c] = this;
    children = unique_ptr<TrieNode *[]>(new TrieNode *[ASCII_COUNT]());
}

TrieNode::~TrieNode() {
    parent->children[c] = nullptr;
}

char TrieNode::get_char() {
    return c;
}

TrieNode* TrieNode::get_parent() {
    return parent;
}

TrieNode** TrieNode::get_children() {
    return children.get();
}


Trie::Trie() {
    root = unique_ptr<TrieNode>(new TrieNode());
}

Trie::~Trie() {
    
}

TrieNode* Trie::get_root() {
    return root.get();
}

bool Trie::contains(const string& s) {
    auto node = root.get();
    
    for (int i = 0; i < s.size(); i++) {
        auto next = node->get_children()[s[i]];
        
        if (next != nullptr) {
            node = next;
        } else {
            return false;
        }
    }
    
    return true;
}
