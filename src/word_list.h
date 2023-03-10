//
// Created by Lenovo on 2023/3/8.
//

#ifndef INC_2023SE_WORD_LIST_WORD_LIST_H
#define INC_2023SE_WORD_LIST_WORD_LIST_H
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cassert>
#include <set>
#include <sstream>
#include <stdio.h>

using namespace std;
enum class Option {
    N_ALL_CHAIN,
    W_MAX,
    C_MAX,
    DEFAULT
};

struct StringCmp{
    bool operator() (const string *a, const string *b) const{
        if (a->length() != b->length()){
            return a->length() < b->length();
        }
        return a->compare(*b) < 0;
    }
};

typedef set<string*, StringCmp> setString;

static char tail = 0, head = 0, reject = 0;
static bool isRing = false;
static Option option = Option::DEFAULT;

#define MAX_LEN 1000


class word_list {

};


#endif //INC_2023SE_WORD_LIST_WORD_LIST_H
