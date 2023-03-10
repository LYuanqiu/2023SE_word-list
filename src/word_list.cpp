//
// Created by Lenovo on 2023/3/8.
//

// 读文件 预处理
#include "word_list.h"
#include "Core.h"
#include "ExceptionHandler.h"

using namespace std;


int isChar(char *str) {
    int length = strlen(str);
    if (length > 1) {
        return -1;
    } else if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')) {
        return 0;
    } else {
        return -2;
    }
}

int readCommand(int argc, char *argv[], char **wordsR[], int* len) {
    for (int i = 1; i < argc - 1; i++) {
        //if (argv[i] == "-n") {
        if (strcmp(argv[i], "-n") == 0) {
            if (option == Option::DEFAULT && tail == 0 && head == 0 && !isRing) {
                option = Option::N_ALL_CHAIN;
            } else {
                handleExceptionWithExit(CONFLICT_OP, "-n");
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (option == Option::DEFAULT) {
                option = Option::C_MAX;
            } else {
                handleExceptionWithExit(CONFLICT_OP, "-c");
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            if (option == Option::DEFAULT) {
                option = Option::W_MAX;
            } else {
                handleExceptionWithExit(CONFLICT_OP, "-w");
            }
        } else if (strcmp(argv[i], "-j") == 0) {
            int r;
            if (reject != 0) {
                handleExceptionWithExit(CONFLICT_OP, "-j");
            } else if ((r = isChar(argv[i + 1]) != 0)) {
                if (r == -1) {
                    handleExceptionWithExit(J_LONG_ALPHA,argv[i+1]);
                } else {
                    handleExceptionWithExit(J_NO_ALPHA, "str");
                }
            } else if (option == Option::N_ALL_CHAIN) {
                handleExceptionWithExit(CONFLICT_OP, "-j");
            } else {
                reject = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            int r;
            if (head != 0) {
                handleExceptionWithExit(CONFLICT_OP, "-h");
            } else if ((r = isChar(argv[i + 1])) != 0) {
                if (r == -1) {
                    handleExceptionWithExit(H_LONG_ALPHA,argv[i+1]);
                } else {
                    handleExceptionWithExit(H_NO_ALPHA, "str");
                }
            } else if (option == Option::N_ALL_CHAIN) {
                handleExceptionWithExit(CONFLICT_OP, "-h");
            } else {
                head = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            int r;
            if (tail != 0) {
                handleExceptionWithExit(CONFLICT_OP, "-t");
            } else if ((r = isChar(argv[i + 1])) != 0) {
                if (r == -1) {
                    handleExceptionWithExit(T_LONG_ALPHA,argv[i+1]);
                } else {
                    handleExceptionWithExit(T_NO_ALPHA, "str");
                }
            } else if (option == Option::N_ALL_CHAIN) {
                handleExceptionWithExit(CONFLICT_OP, "-t");
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
        handleExceptionWithExit(NOT_TXT,argv[argc - 1]);
    }
    static vector<char *> words;
    string filename = argv[argc - 1];
    ifstream fin(filename.c_str(),ios::in | ios::binary | ios::ate);
    if (fin.is_open()) {
        static ios::pos_type size = fin.tellg();
        static string raw_input(size,0);
        fin.seekg(0);
        fin.read(&raw_input[0], size);
        for (int i = 0, first = -1; i < size; i++) {
            char &c = raw_input[i];
            if (c >= 'a' && c <= 'z') {
                if (i != first) words.push_back(&c);
                first = i + 1;
            } else if (c >= 'A' && c <= 'Z') {
                if (i != first) words.push_back(&c);
                c = c | (char) 0x20;
                first = i + 1;
            } else {
                c = 0;
            }
        }
        if (words.empty()) {
            handleExceptionWithExit(NO_WORDS, argv[argc - 1]);
        }
    } else {
        handleExceptionWithExit(OPEN_FAILED, argv[argc - 1]);
    }
    *len = (int) words.size();
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
    argc = 7;
    argv[0] = "exe";
    argv[1] = "-w";
    argv[2] = "-h";
    argv[3] = "z";
    argv[4] = "-t";
    argv[5] = "v";
    argv[6] = "test.txt";

    int len;
    readCommand(argc, argv, words, &len);
    static char buffer[MAX_NUM][MAX_LENGTH];
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
    if(option == Option::N_ALL_CHAIN){
        if(ret > 0){
            outPut(results, ret, "solution.txt", option);
        } else if (ret == -1){
            handleExceptionWithExit(HAS_RING, " ");
        } else {
            handleExceptionWithExit(NO_CHAIN, " ");
        }
    } else {
        if(ret >= 2){
            outPut(results, ret, "solution.txt", option);
        }  else if (ret == -1) {
            handleExceptionWithExit(HAS_RING, " ");
        } else {
            handleExceptionWithExit(NO_CHAIN, " ");
        }
    }
}

# ifdef _WIN32
extern "C" {
    __declspec(dllexport) int __stdcall gen_chains_all(char* words[], int len, char* result[]);
    __declspec(dllexport) int __stdcall gen_chain_word(char* words[], int len, char* result[], char headChar, char tailChar, char rejectChar, bool enable_loop);
    __declspec(dllexport) int __stdcall gen_chain_char(char* words[], int len, char* result[], char headChar, char tailChar, char rejectChar, bool enable_loop);
}

__declspec(dllexport) int __stdcall gen_chains_all(char* words[], int len, char* result[]) {
    return Core::gen_chains_all(words, len, result);
}
__declspec(dllexport) int __stdcall gen_chain_word(char* words[], int len, char* result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
    return Core::gen_chain_word(words, len, result, headChar, tailChar, rejectChar, enable_loop);
}
__declspec(dllexport) int __stdcall gen_chain_char(char* words[], int len, char* result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
    return Core::gen_chain_char(words, len, result, headChar, tailChar, rejectChar, enable_loop);
}

# endif