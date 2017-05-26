//
//  trie.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/13/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef trie_hpp
#define trie_hpp

#include <stdio.h>

#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "define.h"

using namespace std;

const int ASCII_COUNT = 128;

class TrieNode {
private:
    char c;
    bool terminal = false;
    
    tnode_t parent;
    uptr_t<tnode_t[]> children;

public:
    TrieNode();
    TrieNode(const char& c, TrieNode& p);
    ~TrieNode();
    
    char get_char();
    bool is_terminal();
    
    tnode_t get_parent();
    tnode_t* get_children();
    
    void add_child(const char& c);
    void set_terminal(bool t);
};

class Trie {
private:
    uptr_t<TrieNode> root;
    
    void populate(ifstream& in_stream);
    
public:
    Trie();
    Trie(ifstream& in_stream);
    ~Trie();
    
    tnode_t get_root();
    
    void insert(const string& s);
    
    bool contains(const string& s);
    int contains(const string& s, int pos);
    
    void remove(tnode_t node);
};

#endif /* trie_hpp */
