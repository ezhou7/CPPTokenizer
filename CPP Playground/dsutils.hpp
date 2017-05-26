//
//  dsutils.hpp
//  CPP Playground
//
//  Created by Ethan Zhou on 5/8/17.
//  Copyright © 2017 NA. All rights reserved.
//

#ifndef dsutils_hpp
#define dsutils_hpp

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

#include "define.h"
#include "trie.hpp"

using namespace std;

hset_t<string>* create_strset(ifstream& in_stream);
Trie* create_trie(ifstream& in_stream);

#endif /* dsutils_hpp */
