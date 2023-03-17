//
// Created by Lenovo on 2023/3/8.
//

#ifndef INC_2023SE_WORD_LIST_CORE_H
#define INC_2023SE_WORD_LIST_CORE_H
#define CORE

#ifdef CORE
#define EXPOSED_FUNCTION extern "C" _declspec(dllexport)
#else
#define EXPOSED_FUNCTION extern "C" _declspec(dllimport)
#endif
#define CORE_HAS_RING -1

#include "N_Slover.h"
#include "W_Slover.h"
#include "C_Solver.h"
#include "word_list.h"
#include "MaxWordWithRing.h"



static int m;
static vector<string> s;
static int edge[26][26];
int color[26] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
bool flag = false;
struct Core {
    
    static void dfs(int x, set<string> words[26][26]) {
        if (flag)
        {
            return;
        }
        color[x] = 0;
        for (int i = 0; i < 26; i++)
        {
            if (i == x || words[x][i].size() == 0 || color[i] == 1) {
                continue;
            }
            if (color[i] == -1)
            {
                dfs(i, words);
            }
            else if (color[i] == 0)
            {
                flag = true;
                return;
            }
        }
        color[x] = 1;
    }
    static bool hasRing(set<string> words[26][26]) {
        for (int i = 0; i < 26; i++) {
            if (color[i] == -1) {
                dfs(i, words);
            }
        }
        return flag;
    }



    static void init_words(char* words[], int len){
        s.clear();
        for(int i = 0;i < len;i++){
            string S = words[i];
            s.push_back(S);
        }
        m = (int)s.size();
    }

    static void genMap(char *words[], int len, set<string> wordMap[26][26], char rejectChar) {
        init_words(words,len);
        for (int i = 0; i < m; i++) {
            if (s[i][0] == rejectChar) {
                continue;
            } else {
                wordMap[s[i][0] - 'a'][s[i].back() - 'a'].insert(s[i]);
            }
        }
    }
    static void setEdge(set<string> word[26][26]) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                edge[i][j] = word[i][j].size();
            }
        }
    }
    static void my_strcpy(char* dst, const char* src, int size) {
        while (size--) {
            *dst = *src;
            dst++;
            src++;
        }
    }

    static void convertVectorToStringArray(vector<string> &vec, char* result[]) {
        int i = 0;
        for (int j = 0; j < vec.size(); j++) {
            if(vec[j].size() > MAX_LENGTH){
                throw runtime_error("result too long!");
            }
            
            result[j] = (char*)malloc( vec[j].size() + 1 );
            //memset(result[j], 0, sizeof(result[j]));
        }
        for(auto str : vec){
            const char* cstr = str.c_str();
            my_strcpy(result[i], cstr, str.size());
            assert(result[i] != NULL);
            result[i][str.size()] = '\0';
            i++;
        }
    }

    static int gen_chains_all(char *words[], int len, char *result[]) {
        vector<string> resultRet;
        set<string> wordsMap[26][26];
        genMap(words, len, wordsMap, '\000');
        setEdge(wordsMap);
        auto solver = new N_Slover(edge, wordsMap, &resultRet);
        int l = solver->solve();
        if(l == CORE_HAS_RING){
            throw runtime_error("There are rings in the file!");
        } else if(l <=0 ){
            throw runtime_error("There is no chain in the file!");
        }
        try{
            convertVectorToStringArray(resultRet, result);
        } catch (runtime_error const &e) {
            throw e;
        }
        return l;
    }


    static int gen_chain_word(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
        set<string> wordsMap[26][26];
        set<string> wordsMapNoReject[26][26];
        vector<string> resultRet;
        genMap(words, len, wordsMap, rejectChar);
        genMap(words, len, wordsMapNoReject, 0);
        if(enable_loop){
            vector<string> resultR;
            auto solver = new MaxWordWithRing(headChar, tailChar, wordsMap, Option::W_MAX);
            resultR = solver->handleMaxWordWithRing();
            if(resultR.size() < 2  ){
                throw runtime_error("There is no chain in the file!");
            }
            try{
                convertVectorToStringArray(resultR, result);
            } catch (runtime_error &e){
                throw e;
            }
            return (int)resultR.size();
        } else {
            if (hasRing(wordsMapNoReject)) {
                throw runtime_error("There are rings in the file!");
            }
            
            setEdge(wordsMap);
            auto solver = new W_Slover(edge, wordsMap, &resultRet, headChar, tailChar,enable_loop);
            int l = solver->solve();
            if(l == CORE_HAS_RING){
                throw runtime_error("There are rings in the file!");
            } else if(l < 2 ){
                throw runtime_error("There is no chain in the file!");
            }
            try{
                convertVectorToStringArray(resultRet, result);
            } catch (runtime_error &e) {
                throw e;
            }
            return l;
        }
    }


    static int gen_chain_char(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
        set<string> wordsMap[26][26];
        set<string> wordsMapNoReject[26][26];
        vector<string> resultRet;
        genMap(words, len, wordsMap, rejectChar);
        genMap(words, len, wordsMapNoReject, 0);
        if(enable_loop){
            vector<string> resultR;
            auto solver = new MaxWordWithRing(headChar, tailChar, wordsMap, Option::C_MAX);
            resultR = solver->handleMaxWordWithRing();
            if(resultR.size() < 2){
                throw runtime_error("There is no chain in the file!");
            }
            try{
                convertVectorToStringArray(resultR, result);
            } catch (runtime_error &e){
                throw e;
            }
            return (int)resultR.size();
        } else {
            if (hasRing(wordsMapNoReject)) {
                throw runtime_error("There are rings in the file!");
            }

            setEdge(wordsMap);
            auto solver = new C_Slover(edge, wordsMap, &resultRet, headChar, tailChar,enable_loop);
            int l = solver->solve();
            if(l == CORE_HAS_RING){
                throw runtime_error("There are rings in the file!");
            } else if(l < 2){
                throw runtime_error("There is no chain in the file!");
            }
            try{
                convertVectorToStringArray(resultRet, result);
            } catch (runtime_error &e) {
                throw e;
            }
            return l;
        }

    }
};


#endif //INC_2023SE_WORD_LIST_CORE_H
