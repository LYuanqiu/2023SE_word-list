//
// Created by Lenovo on 2023/3/8.
//

#ifndef INC_2023SE_WORD_LIST_WORD_LIST_H
#define INC_2023SE_WORD_LIST_WORD_LIST_H
#define FOR_ALPHA(x) for(int x = 0; x < 26; x++)
#define ALPHA_NUM 26
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <set>
#include <sstream>
#include <filesystem>
using namespace std;
enum class Option {
    N_ALL_CHAIN,
    W_MAX,
    C_MAX,
    DEFAULT
};

//enum class ErrorCode{
//    SUCCESS,
//    FILE_NOT_FOUND,
//    UNKNOWN_OP,
//};

#define UNKNOWN_OP (-1)

static char tail = 0, head = 0, reject = 0;
static bool isRing = false;
static Option option = Option::DEFAULT;

#define MAX_NUM 1000
#define MAX_LENGTH 1000


class word_list {

};


#endif //INC_2023SE_WORD_LIST_WORD_LIST_H
