//
// Created by Lenovo on 2023/3/8.
//
// 实现具体求解函数
#ifndef INC_2023SE_WORD_LIST_ALGORITHM_H
#define INC_2023SE_WORD_LIST_ALGORITHM_H
# include "word_list.h"

class Algorithm{
protected:
    char headChar;
    char tailChar;
    char rejectChar;
    bool isRing;
    setString wordMap[26][26];

private:

public:
    Algorithm(setString wordMap,int *edgeNum[] ,char *result[]){

    }

    Algorithm(setString wordMap,int *edgeNum[] ,char *result[], char headChar, char tailChar, char rejectChar ,bool isRing ){

    }
};
#endif //INC_2023SE_WORD_LIST_ALGORITHM_H
