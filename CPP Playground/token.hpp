//
//  token.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/27/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <stdio.h>

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Token {
private:
    unique_ptr<string> word;
    int start = 0;
    int end = 0;

public:
    Token(const string& s="");
    ~Token();
    
    void setWord(const string& s);
    void setStart(int start);
    void setEnd(int end);
    
    const string* getWord();
    int getStart();
    int getEnd();
};

#endif /* token_hpp */
