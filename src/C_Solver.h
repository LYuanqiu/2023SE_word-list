//
// Created by Lenovo on 2023/3/11.
//

#ifndef INC_2023SE_WORD_LIST_C_SOLVER_H
#define INC_2023SE_WORD_LIST_C_SOLVER_H

#include "queue"
#include "string"
#include "vector"
#include "set"

using namespace std;

class C_Slover {
    char headChar;
    char tailChar;
    int (*edge)[26];
    set<string> (*word)[26];
    char **result;
    int inDegree[26];
    int ringwordLength[26];

public:
    C_Slover(int edge[][26], set<string> word[26][26], char *result[], char headChar, char tailChar, bool isRing) {
        this->edge = edge;
        this->word = word;
        this->headChar = headChar;
        this->tailChar = tailChar;
        this->result = result;
    }

    int solve() {
        return noRingHandler();
    }

private:
    void getInDegree() {
        for (int i = 0;i < 26;i++) {
            inDegree[i] = 0;
            for (int j = 0;j < 26;j++) {
                if (i != j && edge[j][i]) {
                    inDegree[i]++;
                }
            }
        }
    }

    void getInDegree2() {
        for (int i = 0;i < 26;i++) {
            inDegree[i] = 0;
        }
        queue<int> q;
        q.push(headChar - 'a');
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < 26;i++) {
                if (i != x && edge[x][i]) {
                    if (inDegree[i] == 0) {
                        q.push(i);
                    }
                    inDegree[i]++;
                }
            }
        }
        for (int i = 0;i < 26;i++) {
            if (inDegree[i] == 0) {
                inDegree[i] = -1;
            }
        }
        inDegree[headChar - 'a'] = 0;
    }

    int noRingHandler() {
        if (headChar) {
            getInDegree2();
        } else {
            getInDegree();
        }


        for (int i = 0;i < 26;i++) {
            for (int j = 0;j < 26;j++) {
                if (edge[i][j]) {
                    edge[i][j] = 0;
                    string I;
                    for (string s:word[i][j]) {
                        if (edge[i][j] < s.size()) {
                            edge[i][j] = s.size();
                            I = s;
                        }
                    }
                    word[i][j].clear();
                    word[i][j].insert(I);
                }
            }
        }
        queue<int> q;
        int dp[26];
        for (int i = 0;i < 26;i++) {
            dp[i] = -10000;
        }
        int pre[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for (int i = 0;i < 26;i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                dp[i] = edge[i][i];
            }
            pre[i] = -1;
        }

        while (!q.empty()) {
            int front = q.front();
            q.pop();
            for (int i = 0;i < 26;i++) {
                if (i != front && edge[front][i]) {
                    if (edge[front][i] + edge[i][i] + dp[front] > dp[i]) {
                        dp[i] = edge[front][i] + edge[i][i] + dp[front];
                        pre[i] = front;
                    }
                    inDegree[i]--;
                    if (inDegree[i] == 0) {
                        q.push(i);
                    }
                }
            }
        }
        int final = -1, ret;
        if (tailChar) {
            final = tailChar - 'a';
            ret = dp[tailChar - 'a'];
        } else {
            ret = 0;
            for (int i = 0;i < 26;i++) {
                if (dp[i] > ret) {
                    ret = dp[i];
                    final = i;
                }
            }
        }
        vector<string> ans;
        while (true) {
            if (edge[final][final]) {
                for (string str: word[final][final]) {
                    ans.push_back(str);
                    break;
                }
            }
            if (pre[final] >= 0) {
                for (string str: word[pre[final]][final]) {
                    ans.push_back(str);
                    final = pre[final];
                    break;
                }
            } else {
                break;
            }
        }
        std::reverse(ans.begin(), ans.end());
        return ret;
    }
};


#endif //INC_2023SE_WORD_LIST_C_SOLVER_H
