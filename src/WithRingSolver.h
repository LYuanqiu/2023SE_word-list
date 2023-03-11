//
// Created by 12740 on 3/11/2023.
//

#ifndef INC_2023SE_WORD_LIST_WITHRINGSOLVER_H
#define INC_2023SE_WORD_LIST_WITHRINGSOLVER_H

#include "word_list.h"

class WithRingSolver {
protected:
    vector<string> word;

    vector<vector<int>> buildMap(vector<string> &words) {
        vector<vector<int>> graph(words.size());
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words.size(); j++) {
                if (i == j) {
                    continue;
                }
                if (words[i].back() == words[j].front()) {
                    graph[i].push_back(j);
                }
            }
        }
        return graph;
    }

    vector<vector<int>> buildReversedMap(vector<vector<int>> &map, int size){
        vector<vector<int>> reversedMap(size);
        for (int i = 0; i < size; i++){
            for(int next : map[i]){
                reversedMap[next].push_back(i);
            }
        }
        return reversedMap;
    }

    void dfs(int nowWord, vector<vector<int>> &map, vector<bool> &visited, stack<int> &endTime) {
        visited[nowWord] = true;
        for (int next: map[nowWord]) {
            if (!visited[next]) {
                dfs(next, map, visited, endTime);
            }
        }
        endTime.push(nowWord);
    }

    void reverse_dfs(int nowWord, vector<vector<int>> &reversed_map, vector<bool> &visited, vector<int> &scc) {
        visited[nowWord] = true;
        scc.push_back(nowWord);
        for (int next: reversed_map[nowWord]) {
            if (!visited[next]) reverse_dfs(next, reversed_map, visited, scc);
        }
    }

    vector<vector<int>> getScc_kosaraju(vector<vector<int>> &map, vector<vector<int>> &reversed_map) {
        int n = map.size();
        vector<bool> visited(n, false);
        stack<int> endTime;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, map, visited, endTime);
            }
        }

        vector<vector<int>> sccs;
        fill(visited.begin(), visited.end(), false);
        while (!endTime.empty()) {
            int nowWord = endTime.top();
            endTime.pop();
            if (!visited[nowWord]) {
                vector<int> scc;
                reverse_dfs(nowWord, reversed_map, visited, scc);
                sccs.push_back(scc);
            }
        }

        return sccs;
    }

};

#endif //INC_2023SE_WORD_LIST_WITHRINGSOLVER_H
