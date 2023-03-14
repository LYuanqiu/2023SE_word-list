//
// Created by 12740 on 3/11/2023.
//

#ifndef INC_2023SE_WORD_LIST_MAXWORDWITHRING_H
#define INC_2023SE_WORD_LIST_MAXWORDWITHRING_H

#include "word_list.h"

class MaxWordWithRing {
private:
    char headChar;
    char tailChar;
    vector<vector<vector<string>>> words;
    vector<vector<vector<int>>> weights;
    vector<vector<int>> edgeNum;
    int alpha2scc[26];
    int scc_tot = 0;
    vector<vector<int>> sccs;
    vector<vector<bool>> sccEdge;
    vector<int> sccInDegree;
    vector<int> sccOutDegree;
    int maxLength[26][26];
    int maxWeight[26][26];
    int route[200];
    int used[26][26];
    int maxRoute[26][26][200];

    int dfn[26], low[26];
    stack<int> st;
    bool visited[26];
    bool ins[26];
    int time = 0;

    vector<int> getInDegree(vector<vector<int>> &edgeNum_) {
        vector<int> inDegree(ALPHA_NUM);
        FOR_ALPHA(i) {
            inDegree[i] = 0;
            FOR_ALPHA(j) {
                if (i != j && edgeNum_[j][i]) {
                    inDegree[i]++;
                }
            }
        }
        return inDegree;
    }

    vector<int> getOutDegree(vector<vector<int>> &edgeNum_) {
        vector<int> outDegree(ALPHA_NUM);
        FOR_ALPHA(i) {
            outDegree[i] = 0;
            FOR_ALPHA(j) {
                if (i != j && edgeNum_[i][j]) {
                    outDegree[i]++;
                }
            }
        }
        return outDegree;
    }

    void getEdgeNum(vector<vector<vector<string>>> &words_, vector<vector<int>> &edgeNum_, Option option) {
        FOR_ALPHA(i) {
            FOR_ALPHA(j) {
                edgeNum_[i][j] = (int) words_[i][j].size();
                for (auto s: words_[i][j]) {
                    if (option == Option::W_MAX) {
                        weights[i][j].push_back(1);
                    } else {
                        weights[i][j].push_back(s.length());
                    }
                }
            }
        }
        vector<int> inDegree = getInDegree(edgeNum_);
        vector<int> outDegree = getOutDegree(edgeNum_);
        FOR_ALPHA(i) {
            FOR_ALPHA(j) {
                if (i != j) {
                    if (edgeNum_[i][j]
                        && !inDegree[i]
                        && !edgeNum_[i][i]
                        && !outDegree[j]
                        && !edgeNum_[j][j]
                            ) {
                        edgeNum_[i][j] = 0;
                        words_[i][j].clear();
                    }
                } else if (edgeNum_[i][j] == 1
                           && !inDegree[i]
                           && outDegree[j]) {
                    edgeNum_[i][j] = 0;
                    words_[i][j].clear();
                }
                //cout << edgeNum[i][j] << endl;
            }
        }

    }

    void dfs_scc(int alpha) {
        dfn[alpha] = low[alpha] = ++time;
        st.push(alpha);
        visited[alpha] = ins[alpha] = true;
        FOR_ALPHA(i) {
            if (i == alpha || !edgeNum[alpha][i]) {
                continue;
            }
            if (!dfn[i]) {
                dfs_scc(i);
                low[alpha] = min(low[alpha], low[i]);
            } else if (ins[i]) {
                low[alpha] = min(low[alpha], low[i]);
            }
        }
        if (dfn[alpha] == low[alpha]) {
            while (true) {
                int tmp = st.top();
                st.pop();
                ins[tmp] = false;
                sccs[scc_tot].push_back(tmp);
                alpha2scc[tmp] = scc_tot;
                if (tmp == alpha) break;
            }
            scc_tot++;
        }
    }

    void get_scc() {
        memset(visited, false, sizeof(visited));
        FOR_ALPHA(i) {
            if (dfn[i] == 0) dfs_scc(i);
        }
        FOR_ALPHA(i) {
            FOR_ALPHA(j) {
                if (alpha2scc[i] != alpha2scc[j] && edgeNum[i][j]) {
                    sccEdge[alpha2scc[i]][alpha2scc[j]] = true;
                }
            }
        }
        for (int i = 0; i < scc_tot; i++) {
            for (int j = 0; j < scc_tot; j++) {
                if (sccEdge[i][j]) {
                    sccInDegree[j]++;
                    sccOutDegree[i]++;
                }
            }
        }
    }

    vector<bool> findReachableAlphaStart(int start, set<string> words_[26][26], vector<bool> &reachable) {
        vector<bool> visited_bfs(ALPHA_NUM, false);
        queue<int> q;
        q.push(start);
        visited_bfs[start] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            FOR_ALPHA(i) {
                if (words_[now][i].size() > 0 && !visited_bfs[i] && reachable[i]) {
                    q.push(i);
                    visited_bfs[i] = true;
                }
            }
        }
        return visited_bfs;
    }

    vector<bool> findReachableAlphaEnd(int end, set<string> words_[26][26], vector<bool> &reachable) {
        vector<bool> visited_bfs(ALPHA_NUM, false);
        queue<int> q;
        q.push(end);
        visited_bfs[end] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            FOR_ALPHA(i) {
                if (words_[i][now].size() > 0 && !visited_bfs[i] && reachable[i]) {
                    q.push(i);
                    visited_bfs[i] = true;
                }
            }
        }
        return visited_bfs;
    }

    vector<vector<vector<string>>> toVectorWords(set<string> words_[26][26]) {
        vector<vector<set<string>>> wordlist_set(ALPHA_NUM, vector<set<string>>(ALPHA_NUM, set<string>()));
        vector<vector<vector<string>>> wordlist(ALPHA_NUM, vector<vector<string>>(ALPHA_NUM, vector<string>()));
        vector<bool> reachableAlpha(ALPHA_NUM, true);
        if (headChar) {
            reachableAlpha = findReachableAlphaStart(headChar - 'a', words_, reachableAlpha);
        }
        if (tailChar) {
            reachableAlpha = findReachableAlphaEnd(tailChar - 'a', words_, reachableAlpha);
        }
        FOR_ALPHA(i) {
            FOR_ALPHA(j) {
                if (reachableAlpha[i] && reachableAlpha[j]) {
                    for (const auto &word: words_[i][j]) {
                        wordlist_set[i][j].insert(word);
                    }
                }
            }
        }
        FOR_ALPHA(i) {
            FOR_ALPHA(j) {
                vector<string> v;
                v.assign(wordlist_set[i][j].begin(), wordlist_set[i][j].end());
                wordlist[i][j] = v;
            }
        }
        return wordlist;
    }

    void bfsFormStart(int start, vector<set<int>> &sccInFromStart) {
        bool visited_bfs[26];
        memset(visited_bfs, false, sizeof(visited_bfs));
        queue<int> q;
        q.push(start);
        visited_bfs[start] = true;
        sccInFromStart[alpha2scc[start]].insert(start);
        while (!q.empty()) {
            int front = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (edgeNum[front][i]) {
                    if (!visited_bfs[i]) {
                        q.push(i);
                        visited_bfs[i] = true;
                    }
                    if (alpha2scc[front] != alpha2scc[i]) {
                        sccInFromStart[alpha2scc[i]].insert(i);
                    }
                }
            }
        }
    }

    //找同一个scc里的最长路径
    void dfs_word(int cur, int start, int length, int total_weight) {
        //路径记录
        route[length] = cur;
        if (total_weight > maxWeight[start][cur]) {
            for (int i = 0; i <= length; i++) {
                maxRoute[start][cur][i] = route[i];
            }
            maxLength[start][cur] = length;
            maxWeight[start][cur] = total_weight;
        }
        //下一个节点
        for (auto &i: sccs[alpha2scc[start]]) {
            if (edgeNum[cur][i] > used[cur][i]) {
                used[cur][i]++;
                dfs_word(i, start, length + 1, total_weight + weights[cur][i][edgeNum[cur][i] - used[cur][i]]);
                used[cur][i]--;
            }
        }
    }


public:
    MaxWordWithRing(char head, char tail, set<string> words_[26][26], Option option) :
            headChar(head), tailChar(tail) {
        words = toVectorWords(words_);
        edgeNum = vector<vector<int>>(ALPHA_NUM, vector<int>(ALPHA_NUM));
        weights = vector<vector<vector<int>>>(ALPHA_NUM, vector<vector<int>>(ALPHA_NUM, vector<int>()));

        getEdgeNum(words, edgeNum, option);
        sccs = vector<vector<int>>(26, vector<int>());
        sccEdge = vector<vector<bool>>(26, vector<bool>(26, false));
        sccInDegree = vector<int>(26, 0);
        sccOutDegree = vector<int>(26, 0);
        memset(visited, false, sizeof(visited));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(ins, false, sizeof(ins));
        memset(alpha2scc, 0, sizeof(alpha2scc));
        memset(maxWeight, 0, sizeof(maxWeight));
        memset(route, 0, sizeof(route));
    }

    vector<string> handleMaxWordWithRing() {

        get_scc();
        vector<set<int>> sccInFromStart(26, set<int>());
        if (headChar) {
            bfsFormStart(headChar - 'a', sccInFromStart);
        } else {
            FOR_ALPHA(i) {
                if (sccInDegree[alpha2scc[i]] == 0) {
                    bfsFormStart(i, sccInFromStart);
                }
            }
        }
        memset(maxWeight, -10000, sizeof (maxWeight));

        for (int i = 0; i < scc_tot; i++) {
            for (auto &j: sccInFromStart[i]) {
                memset(used, 0, sizeof(used));
                maxWeight[j][j] = 0;
                dfs_word(j, j, 0, 0);
            }
        }
        queue<int> q;
        int innerLast[26], outerLast[26], maxInWeight[26], maxOutWeight[26];
        memset(innerLast, 0, sizeof(innerLast));
        memset(maxInWeight, 0, sizeof(maxInWeight));
        memset(maxOutWeight, 0, sizeof(maxOutWeight));
        for (int i = 0; i < scc_tot; i++) {
            if (sccInDegree[i] == 0) {
                q.push(i);
            }
        }
        FOR_ALPHA(i) {
            outerLast[i] = -1;
            maxOutWeight[i] = -10000;
        }
        vector<int> outDegree = getOutDegree(edgeNum);
        while (!q.empty()) {
            int front = q.front();
            q.pop();
            for (auto &i: sccs[front]) {
                for (auto &j: sccs[front]) {
                    if (maxInWeight[j] + maxWeight[j][i] > maxOutWeight[i]) {
                        maxOutWeight[i] = maxInWeight[j] + maxWeight[j][i];
                        innerLast[i] = j;
                    }
                }
            }
            for (int i = 0; i < scc_tot; i++) {
                if (sccEdge[front][i]) {
                    for (auto &j: sccs[front]) {
                        for (auto &k: sccs[i]) {
                            if (edgeNum[j][k] && maxOutWeight[j] + weights[j][k].back() > maxInWeight[k] &&
                                (maxOutWeight[j] > 0 || outDegree[k] || edgeNum[k][k])) {
                                maxInWeight[k] = maxOutWeight[j] + weights[j][k].back();
                                outerLast[k] = j;
                            }
                        }
                    }
                    sccInDegree[i]--;
                    if (sccInDegree[i] == 0) {
                        q.push(i);
                    }
                }
            }

        }
        int final = -1, ret;
        if (tailChar) {
            final = tailChar - 'a';
            ret = maxOutWeight[tailChar - 'a'];
        } else {
            ret = 0;
            FOR_ALPHA(i) {
                if (maxOutWeight[i] > ret) {
                    ret = maxOutWeight[i];
                    final = i;
                }
            }
        }

        stack<int> stk;
        while (final >= 0) {
            stk.push(final);
            stk.push(innerLast[final]);
            final = outerLast[innerLast[final]];
        }
        vector<string> resultR;
        while (!stk.empty()) {
            int entrance = stk.top();
            stk.pop();
            int exit = stk.top();
            int *finish = maxRoute[entrance][exit] + maxLength[entrance][exit];
            for (int *i = maxRoute[entrance][exit] + 1; i <= finish; i++) {
                resultR.push_back(words[*(i - 1)][*i].back());
                words[*(i - 1)][*i].pop_back();
            }
            stk.pop();
            if (stk.empty()) {
                break;
            }
            resultR.push_back(words[exit][stk.top()].back());
            words[exit][stk.top()].pop_back();
        }
        
        return resultR;
    }
};


#endif //INC_2023SE_WORD_LIST_MAXWORDWITHRING_H
