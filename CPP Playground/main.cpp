//
//  main.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include <iostream>
#include <string>
#include <regex>
#include <memory>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    string s = "Some people are careless.";
    
    unique_ptr<basic_regex<char>> uniq_re(new basic_regex<char>("\\w+"));
    bool match = regex_search(s, *(basic_regex<char> *) uniq_re.get());
    
    cout << ((match) ? "Match" : "No match") << endl;
    
    return 0;
}
