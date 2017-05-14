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

#include <memory>
#include <string>

using namespace std;

const int ASCII_COUNT = 128;

class TrieNode {
private:
    char c;
    
    TrieNode *parent;
    unique_ptr<TrieNode *[]> children;

public:
    TrieNode();
    TrieNode(const char& c, TrieNode& p);
    ~TrieNode();
    
    char get_char();
    TrieNode* get_parent();
    TrieNode** get_children();
};

class Trie {
private:
    unique_ptr<TrieNode> root;
    
public:
    Trie();
    ~Trie();
    
    TrieNode* get_root();
    
    bool contains(const string& s);
};

#endif /* trie_hpp */
