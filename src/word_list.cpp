//
// Created by Lenovo on 2023/3/8.
//

// 读文件 预处理
#include "word_list.h"
#include "Core.h"

using namespace std;


void a(char *s[]) {

}

int isChar(char *str) {
    int length = strlen(str);
    if (length > 1) {
        return -1; //option 报错
    } else if ((str[0] >= 'A' && str[0] <= 'Z') or (str[0] >= 'a' && str[0] <= 'z')) {
        return 0;
    } else {
        return -2; // option 报错
    }
}

int readCommand(int argc, char *argv[], char **wordsR[], int* len) {
    for (int i = 1; i < argc - 1; i++) {
        //if (argv[i] == "-n") {
        if (strcmp(argv[i], "-n") == 0) {
            if (option == Option::DEFAULT && tail == 0 && head == 0 && !isRing) {
                option = Option::N_ALL_CHAIN;
            } else {
                // option  处理参数冲突
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (option == Option::DEFAULT) {
                option = Option::C_MAX;
            } else {
                //
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            if (option == Option::DEFAULT) {
                option = Option::W_MAX;
            } else {
                //
            }
        } else if (strcmp(argv[i], "-j") == 0) {
            int r;
            if (reject != 0) {
                // 报错
            } else if ((r = isChar(argv[i + 1]) != 0)) {
                // 根据r值报错
            } else if (option == Option::N_ALL_CHAIN) {
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
            } else if (option == Option::N_ALL_CHAIN) {
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
            } else if (option == Option::N_ALL_CHAIN) {
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
    static vector<char *> words;
    int cntw = 0;
    string filename = argv[argc - 1];
    ifstream fin(filename.c_str(),ios::in | ios::binary | ios::ate);
    string strLine;
    static ios::pos_type size = fin.tellg();
    fin.seekg(0);

    static string raw_input(size,0);
    if (fin.is_open()) {
        fin.read(&raw_input[0], size);
            for (int i = 0, first = -1; i < size; i++) {
                char &c = raw_input[i];
                if (c >= 'a' && c <= 'z') {
                    if (i != first) words.push_back(&c);
                    first = i + 1;
                } else if (c >= 'A' && c <= 'Z') {
                    if (i != first) words.push_back(&c);
                    c = ::tolower(c);
                    first = i + 1;
                } else {
                        c = 0;
                }
            }
    } else {
        // TODO:报错
    }
    *len = words.size();
    *wordsR = words.data();
    fin.close();
    return 0;
}

void outPut(char*result[], int len, string outputFileName, Option op){
    ofstream outFile(outputFileName);
    if(outFile.is_open()){
        if(op == Option::N_ALL_CHAIN){
            cout << len << endl;
            outFile << len << endl;
        }
        for(int i = 0; i < len; i++){
            cout << result[i] << endl;
            outFile << result[i] << endl;
        }
    } else {
        cerr << "Failed to open output file" << endl;
    }
}

// option 处理文件 以及 报错


int main(int argc, char *argv[]) {

    char **words[MAX_LENGTH];
    argc = 4;
    argv[0] = "exe";
    argv[1] = "-c";
    argv[2] = "-r";
    argv[3] = "./test.txt";
    int len;
    readCommand(argc, argv, words, &len);
    char buffer[MAX_NUM][MAX_LENGTH];
    char *results[MAX_NUM];
    for(int i=0;i<MAX_NUM;i++){
        results[i] = buffer[i];
    }
    int ret;
    switch (option) {
        case Option::N_ALL_CHAIN:
            ret = Core::gen_chains_all(*words, len , results);
            break;
        case Option::W_MAX:
            ret = Core::gen_chain_word(*words, len, results, head, tail, reject,
                                 isRing);
            break;
        case Option::C_MAX:
            ret = Core::gen_chain_char(*words, len, results, head, tail, reject,
                                 isRing);
            break;
        default:
           ret = UNKNOWN_OP;
    }
    if(ret > 2){
        outPut(results, ret, "solution.txt", option);
    }
}