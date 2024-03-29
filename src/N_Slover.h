//
// Created by Lenovo on 2023/3/11.
//

#ifndef INC_2023SE_WORD_LIST_N_SLOVER_H
#define INC_2023SE_WORD_LIST_N_SLOVER_H
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <set>
#include <sstream>

using namespace std;
static char *ans[1000];
static vector<string> result;
class N_Slover {

public:
    N_Slover(int edge[26][26], set<string> word[26][26], vector<string> *r) {
        this->edge = edge;
        this->word = word;
        this->resultR = r;

    }

    int solve() {
        if (hasRing()) {
            return -1;
        }
        for (int i = 0; i < 26; i++)
            dfs_getResult(i, 0);

        int l = 0;
        for (vector<string> s:result_tmp) {
            string string1 = s[0];
            for (int i = 1;i < s.size();i++) {
                string1 = string1 + " " + s[i];
            }
            result.push_back(string1);
            l += 1;
        }
        *resultR = result;
        return l;
    }

private:
    set<string> (*word)[26];
    int (*edge)[26];
    vector<string> *resultR;


    /*
     * 利用深度优先遍历判断是否有环
     */
    int color[26] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    bool flag = false;
    void dfs(int x) {
        if (flag)
        {
            return;
        }
        color[x] = 0;
        for (int i = 0; i < 26; i++)
        {
            if (i == x || edge[x][i] == 0 || color[i] == 1) {
                if (i == x && edge[x][i] > 1) {
                    flag = true;
                }
                continue;
            }
            if (color[i]==-1)
            {
                dfs(i);
            }
            else if (color[i]==0)
            {
                flag = true;
                return;
            }
        }
        color[x] = 1;
    }
    bool hasRing() {
        for (int i = 0;i < 26;i++) {
            if (color[i] == -1) {
                dfs(i);
            }
        }
        return flag;
    }

    /*
     * 用深度遍历求解所有单词串
     */
    set<vector<string>> result_tmp;
    vector<string> pre;
    bool sameTag = true;
    void dfs_getResult(int x, int len) {
        for (int i = 0; i < 26;i++) {
            if ((i != x || sameTag) && edge[x][i]) {
                if (i == x) {
                    sameTag = false;
                } else {
                    sameTag = true;
                }
                vector<string> tmp;
                tmp.assign(word[x][i].begin(),word[x][i].end());
                for (int j = ((int)word[x][i].size()) - 1; j >= 0; j--) {
                    pre.push_back(tmp[j]);
                    if (len >= 1) {
                        for (int s = 0; s < pre.size() - 1; s++) {
                            vector<string> new_result;
                            for (int t = s; t < pre.size(); t++) {
                                new_result.push_back(pre[t]);
                            }
                            result_tmp.insert(new_result);
                        }
                    }
                    dfs_getResult(i, len + 1);
                    pre.pop_back();
                }
            }
        }
    }
};


#endif //INC_2023SE_WORD_LIST_N_SLOVER_H
