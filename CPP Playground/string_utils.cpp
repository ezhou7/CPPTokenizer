//
//  string_utils.cpp
//  CPP Playground
//
//  Created by Ethan Zhou on 4/24/17.
//  Copyright © 2017 NA. All rights reserved.
//

#include "string_utils.hpp"

bool is_equal(const string *s1, const string *s2) {
    return s1->compare(*s2) == 0;
}
