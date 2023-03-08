//
// Created by Lenovo on 2023/3/8.
//
#include "word_list.h"
void a(char * s[]) {
    cout << s[0] << endl;
}

int isChar(char *str) {
    int length = strlen(str);
    if (length > 1) {
        return -1; //todo 报错
    } else if ((str[0] >= 'A' && str[0] <= 'Z') or (str[0] >= 'a' && str[0] <= 'z')) {
        return 0;
    } else {
        return -2; // todo 报错
    }
}

void readCommand(int argc, char *argv[]) {
    for (int i = 1; i < argc - 1; i++) {
        //if (argv[i] == "-n") {
        if (strcmp(argv[i], "-n") == 0) {
            if (todo == TodoOption::DEFAULT && tail == 0 && head == 0 && !isRing) {
                todo = TodoOption::N_ALL_CHAIN;
            } else {
                // todo  处理参数冲突
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (todo == TodoOption::DEFAULT) {
                todo = TodoOption::C_MAX;
            } else {
                //
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            if (todo == TodoOption::DEFAULT) {
                todo = TodoOption::W_MAX;
            } else {
                //
            }
        } else if (strcmp(argv[i], "-j") == 0) {
            int r;
            if (reject != 0) {
                // 报错
            } else if ((r = isChar(argv[i + 1]) != 0)) {
                // 根据r值报错
            } else if (todo == TodoOption::N_ALL_CHAIN) {
                // n冲突
            } else {
                reject = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            int r;
            if (head != 0) {
                //TODO: 已有h
            } else if ((r = isChar(argv[i + 1])) != 0) {
                //TODO:
            } else if (todo == TodoOption::N_ALL_CHAIN) {
                // n冲突
            } else {
                head = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            int r;
            if (tail != 0) {
                //TODO: 已有t
            } else if ((r = isChar(argv[i + 1])) != 0) {
                //TODO:
            } else if (todo == TodoOption::N_ALL_CHAIN) {
                // n冲突
            } else {
                tail = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-r") == 0) {
            int r;
            isRing = true;
        }
    }
    int length = (int) strlen(argv[argc - 1]);
    if (length <= 4 || argv[argc - 1][length - 4] != '.'
        || argv[argc - 1][length - 3] != 't'
        || argv[argc - 1][length - 2] != 'x'
        || argv[argc - 1][length - 1] != 't') {
        //TODO: 文件名错误
    }
    vector<string> words;
    string filename = argv[argc - 1];
    ifstream fin(filename.c_str());
    string strLine;
    if (fin.is_open()) {
        while (getline(fin, strLine)) {
            string word = "";
            length = (int) strlen(strLine.c_str());
            for (int i = 0; i < length; i++) {
                if(strLine.c_str()[i] >= 'a' && strLine.c_str()[i] <= 'z') {
                    word += strLine.c_str()[i];
                } else if (strLine.c_str()[i] >= 'A' && strLine.c_str()[i] <= 'Z')  {
                    word += tolower( strLine.c_str()[i]);
                } else {
                    if (strlen(word.c_str()) > 0) {
                        words.push_back(word);
                        word = "";
                    }
                }
            }
            if (strlen(word.c_str()) > 0) {
                words.push_back(word);
                word = "";
            }
        }
    } else {
        // TODO:报错
    }


    set<string> wordsSet(words.begin(), words.end());

    for(string s : wordsSet){
        cout << s << endl;
    }

    a(reinterpret_cast<char **>(&words[0]));

}


// todo 处理文件 以及 报错


int main(int argc, char *argv[]) {
    argc = 3;
    argv[0] = ".\\word_list.exe";
    argv[1] = "-w";
    argv[2] = "test.txt";
    readCommand(argc, argv);
}