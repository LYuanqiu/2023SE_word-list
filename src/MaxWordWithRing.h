//
// Created by 12740 on 3/11/2023.
//

#ifndef INC_2023SE_WORD_LIST_MAXWORDWITHRING_H
#define INC_2023SE_WORD_LIST_MAXWORDWITHRING_H
#include "word_list.h"
#include "WithRingSolver.h"

class MaxWordWithRing : public WithRingSolver {
private:
    char headChar;
    char tailChar;
    bool allowRing;
    set<string> words[26][26];
    int wordNum[26][26];
    vector<string> result;

    vector<string> toVectorWords(set<string> words[26][26]) {
        vector<string> wordlist;
        FOR_ALPHA(i) {
            FOR_ALPHA(j) {
                for (const auto &word: words[i][j]) {
                    wordlist.push_back(word);
                }
            }
        }
        return wordlist;
    }

    vector<string> reorderWords(vector<string>& words, const vector<string>& maxChainWords, vector<vector<int>> graph) {
        unordered_map<string, int> wordToIndex;
        for (int i = 0; i < words.size(); i++) {
            wordToIndex[words[i]] = i;
        }
        vector<string> reorderedWords;
        for (const string& word : maxChainWords) {
            reorderedWords.push_back(word);
            int index = wordToIndex[word];
            wordToIndex.erase(word);
            for (int i : graph[index]) {
                if (wordToIndex.count(words[i])) {
                    reorderedWords.push_back(words[i]);
                    wordToIndex.erase(words[i]);
                }
            }
        }
        for (const auto& kv : wordToIndex) {
            reorderedWords.push_back(kv.first);
        }
        return reorderedWords;
    }
public:
    MaxWordWithRing(char head, char tail, bool allowRing, set<string> words_[26][26]) :
            headChar(head), tailChar(tail), allowRing(allowRing) {
        FOR_ALPHA(i) {
            FOR_ALPHA(j) words[i][j] = words_[i][j];
        }
    }

    vector<string> handleMaxWordWithRing() {
        vector<string> wordlist = toVectorWords(words);
        vector<vector<int>> map = buildMap(wordlist);
        vector<vector<int>> reversed_map = buildReversedMap(map, (int) wordlist.size());
        vector<vector<int>> sccs = getScc_kosaraju(map, reversed_map);
        vector<int> word_to_scc(wordlist.size());
        unordered_map<int, vector<int>> scc_to_wordlist;
        for (int i = 0; i < sccs.size(); i++) {
            for (int word: sccs[i]) {
                word_to_scc[word] = i;
                scc_to_wordlist[i].push_back(word);
            }
        }
        unordered_map<int, int> scc_to_max_word;
        for (int i = 0; i < sccs.size(); i++) {
            for (int word: sccs[i]) {
                int max_word = 1;
                vector<int> max_wordlist = {word};
                vector<bool> used(wordlist.size(), false);
                used[word] = true;
                for (int next: reversed_map[word]) {
                    if (word_to_scc[next] != i) {
                        int len = 2;
                        vector<int> wordlist_ = {word, next};
                        used[next] = true;
                        for (int nn: reversed_map[next]) {
                            if (used[nn]) break;
                            if (word_to_scc[nn] == i) {
                                len++;
                                wordlist_.push_back(nn);
                                used[nn] = true;
                                break;
                            }
                            len++;
                            wordlist_.push_back(nn);
                            used[nn] = true;
                        }
                        if (len > max_word) {
                            max_word = len;
                            max_wordlist = wordlist_;
                        }
                    }
                }
                scc_to_max_word[i] = max(scc_to_max_word[i], max_word);
                set<int> unique_wordlist(scc_to_wordlist[i].begin(), scc_to_wordlist[i].end());
                unique_wordlist.insert(max_wordlist.begin(), max_wordlist.end());
                scc_to_wordlist[i] = vector<int>(unique_wordlist.begin(), unique_wordlist.end());
            }
        }
        int max_chain = 0;
        vector<string> max_chain_words;
        for (auto it = scc_to_max_word.begin(); it != scc_to_max_word.end(); ++it) {
            if (it->second > max_chain) {
                max_chain = it->second;
                max_chain_words.clear();
                for (int word_idx: scc_to_wordlist[it->first]) {
                    max_chain_words.push_back(wordlist[word_idx]);
                }
            }
        }
        for (int i = 0; i < max_chain_words.size(); i++) {
            cout << max_chain_words[i] << endl;
        }


        return max_chain_words;
    }
};


#endif //INC_2023SE_WORD_LIST_MAXWORDWITHRING_H
