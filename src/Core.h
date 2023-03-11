//
// Created by Lenovo on 2023/3/8.
//

#ifndef INC_2023SE_WORD_LIST_CORE_H
#define INC_2023SE_WORD_LIST_CORE_H
#include "N_Slover.h"
#include "W_Slover.h"
#include "C_Solver.h"
static int m;
static vector<string> s;
static int edge[26][26];

// 接口类 创建图
struct Core {
    static void init_words(char* words[], int len){
        s.clear();
        for(int i = 0;i < len;i++){
            string S = words[i];
            if(S.length() == 1) continue;
            s.push_back(S);
        }
        m = (int)s.size();
    }
    static void genMap(char *words[], int len, set<string> wordMap[26][26], char rejectChar) {
        init_words(words,len);
        for (int i = 0; i < len; i++) {
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

    /*
     * 求所有的单词链
     * 参数说明
     * words: 处理后的读入的单词
     * len: 单词列表的长度
     * result：单词链
     * 返回单词链的数目
     * */
    static int gen_chains_all(char *words[], int len, char *result[]) {
        set<string> wordsMap[26][26];
        genMap(words, len, wordsMap, '\000');
        setEdge(wordsMap);
        auto solver = new N_Slover(edge, wordsMap, result);
        int l = solver->solve();
        ::printf("%d\n",ans);
        return l;
    }

    /*
     * 找包含单词数目最多的单词链
     *
     * 参数说明
     * words: 处理后的读入的单词
     * len: 单词列表的长度
     * result: 单词链
     * head: 首字母/0为未指定
     * tail: 尾字母/0为未指定
     * except: 不允许出现的首字母/0为未指定
     * enable_loop: 是否允许成环
     * 返回单词链的长度
     *
    * */
    static int gen_chain_word(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
        set<string> wordsMap[26][26];
        genMap(words, len, wordsMap, '\000');
        setEdge(wordsMap);
        auto solver = new W_Slover(edge, wordsMap, result, headChar, tailChar,enable_loop);
        int l = solver->solve();
        return l;
    }


    /*
     * 找包含字母数目最多的单词链
     *
     * 参数说明
     * words: 处理后的读入的单词
     * len: 单词列表的长度
     * result: 单词链
     * head: 首字母/0为未指定
     * tail: 尾字母/0为未指定
     * except: 不允许出现的首字母/0为未指定
     * enable_loop: 是否允许成环
     * 返回单词链的长度
     *
    * */
    static int gen_chain_char(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
        set<string> wordsMap[26][26];
        genMap(words, len, wordsMap, '\000');
        setEdge(wordsMap);
        auto solver = new C_Slover(edge, wordsMap, result, headChar, tailChar,enable_loop);
        int l = solver->solve();
        return l;
    }
};

#endif //INC_2023SE_WORD_LIST_CORE_H
