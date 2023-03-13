//
// Created by Lenovo on 2023/3/11.
//

#ifndef INC_2023SE_WORD_LIST_W_SLOVER_H
#define INC_2023SE_WORD_LIST_W_SLOVER_H

#include "queue"
#include "string"
#include "vector"
#include "set"

using namespace std;

class W_Slover {
    char headChar;
    char tailChar;
    int (*edge)[26];
    set<string> (*word)[26];
    vector<string> result;
    int inDegree[26];

public:
    W_Slover(int edge[][26], set<string> word[26][26], vector<string> &result, char headChar, char tailChar, bool isRing) {
        this->edge = edge;
        this->word = word;
        this->headChar = headChar;
        this->tailChar = tailChar;
        this->result = result;
    }

    int solve() {
        if (hasRing()) {
            return -1;
        }
        return noRingHandler();
    }

private:
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

        queue<int> q;
        int dp[26];
        for (int i = 0;i < 26;i++) {
            dp[i] = -10000;
        }
        int pre[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for (int i = 0;i < 26;i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                dp[i] = (edge[i][i]>0);
            }
            pre[i] = -1;
        }
        while (!q.empty()) {
            int front = q.front();
            q.pop();
            for (int i = 0;i < 26;i++) {
                if (i != front && edge[front][i]) {
                    if (1 + (edge[i][i] > 0) + dp[front] > dp[i]) {
                        dp[i] = 1 + (edge[i][i] > 0) + dp[front];
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
        while (true) {
            if (edge[final][final]) {
                for (string str: word[final][final]) {
                    result.push_back(str);
                    break;
                }
            }
            if (pre[final] >= 0) {
                for (string str: word[pre[final]][final]) {
                    result.push_back(str);
                    final = pre[final];
                    break;
                }
            } else {
                break;
            }
        }
        std::reverse(result.begin(), result.end());
        return ret;
    }
};


#endif //INC_2023SE_WORD_LIST_W_SLOVER_H
