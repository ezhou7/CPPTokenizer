//
//  trie.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "trie.hpp"

/* ------------------- TrieNode Implementation ------------------- */

TrieNode::TrieNode() {
    this->c = 0;
    this->parent = nullptr;
    
    children = unique_ptr<TrieNode *[]>(new TrieNode *[ASCII_COUNT]());
}

TrieNode::TrieNode(const char& c, TrieNode& p) {
    this->c = c;
    this->parent = &p;
    
    p.children[c] = this;
    children = unique_ptr<TrieNode *[]>(new TrieNode *[ASCII_COUNT]());
}

TrieNode::~TrieNode() {
    if (parent != nullptr)
        parent->children[c] = nullptr;
}

char TrieNode::get_char() {
    return c;
}

bool TrieNode::is_terminal() {
    return terminal;
}

TrieNode* TrieNode::get_parent() {
    return parent;
}

TrieNode** TrieNode::get_children() {
    return children.get();
}

void TrieNode::add_child(const char& c) {
    if (children[c] == nullptr)
        children[c] = new TrieNode(c, *this);
}

void TrieNode::set_terminal(bool t) {
    terminal = t;
}


/* ------------------- Trie Implementation ------------------- */

Trie::Trie() {
    root = unique_ptr<TrieNode>(new TrieNode());
}

Trie::Trie(ifstream& in_stream) {
    root = unique_ptr<TrieNode>(new TrieNode());
    populate(in_stream);
}

Trie::~Trie() {
    remove(get_root());
}

TrieNode* Trie::get_root() {
    return root.get();
}

void Trie::populate(ifstream& in_stream) {
    if (!in_stream.is_open()) {
        cout << "File has been closed already.\n";
        return;
    }
    
    string line;
    while (getline(in_stream, line)) {
        insert(line);
    }
    
    in_stream.close();
}

void Trie::insert(const string& s) {
    auto node = get_root();
    
    for (int i = 0; i < s.size(); i++) {
        node->add_child(s[i]);
        node = node->get_children()[s[i]];
    }
    
    node->set_terminal(true);
}

bool Trie::contains(const string& s) {
    return contains(s, 0);
}

int Trie::contains(const string& s, int pos) {
    auto node = root.get();
    
    int i;
    for (i = pos; i < s.size(); i++) {
        if (node->is_terminal())
            return i - pos;
        
        auto next = node->get_children()[s[i]];
        
        if (next != nullptr) {
            node = next;
        } else {
            return 0;
        }
    }
    
    return (node->is_terminal()) ? i - pos : 0;
}

void Trie::remove(TrieNode *node) {
    if (node == nullptr)
        return;
    
    auto children = node->get_children();
    
    for (int i = 0; i < ASCII_COUNT; i++) {
        remove(children[i]);
    }
    
    if (node != get_root())
        delete node;
}
