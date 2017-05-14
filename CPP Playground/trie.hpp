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

using namespace std;

const int ASCII_COUNT = 128;

class TrieNode {
private:
    char c;
    bool terminal = false;
    
    TrieNode *parent;
    unique_ptr<TrieNode *[]> children;

public:
    TrieNode();
    TrieNode(const char& c, TrieNode& p);
    ~TrieNode();
    
    char get_char();
    bool is_terminal();
    
    TrieNode* get_parent();
    TrieNode** get_children();
    
    void add_child(const char& c);
    void set_terminal(bool t);
};

class Trie {
private:
    unique_ptr<TrieNode> root;
    
    void populate(ifstream& in_stream);
    
public:
    Trie();
    Trie(ifstream& in_stream);
    ~Trie();
    
    TrieNode* get_root();
    
    void insert(const string& s);
    
    bool contains(const string& s);
    bool contains(const string& s, int pos);
    
    void remove(TrieNode *node);
};

#endif /* trie_hpp */
