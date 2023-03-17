//
// Created by Lenovo on 2023/3/8.
//


#include "word_list.h"
#include "Core.h"
#include "ExceptionHandler.h"


using namespace std;
//#define INPUT
#ifdef INPUT
#include <libloaderapi.h>
#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllimport) int __stdcall gen_chains_all(int a, int b);
__declspec(dllimport) int __stdcall subtruct(int a, int b);

#ifdef __cplusplus
}
#endif


int DynamicUseN(char *words[], int len, char *result[])
{
    
    HMODULE module = LoadLibrary("core_changed.dll");
    if (module == NULL)
    {
        printf("加载DLLTest1.dll动态库失败\n");
        return 0;
    }
    typedef int (*gen_chains_all)(char **, int , char **);
    gen_chains_all N;
    
    N = (gen_chains_all)GetProcAddress(module, "gen_chains_all");

    int sum  = N(words, len, result);
    return sum;
}

int DynamicUseW(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
   
    HMODULE module = LoadLibrary("core_changed.dll");
    if (module == NULL)
    {
        printf("加载DLLTest1.dll动态库失败\n");
        return 0;
    }
    typedef int (*gen_chain_word)(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop); 
    gen_chain_word W;
    
    W = (gen_chain_word)GetProcAddress(module, "gen_chain_word");

    int sum  = W(words, len, result, headChar, tailChar, rejectChar, enable_loop);
    return sum;
}

int DynamicUseC(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop) {
   
    HMODULE module = LoadLibrary("core_changed.dll");
    if (module == NULL)
    {
        printf("加载DLLTest1.dll动态库失败\n");
        return 0;
    }
    typedef int (*gen_chain_char)(char *words[], int len, char *result[], char headChar, char tailChar, char rejectChar, bool enable_loop); 
    gen_chain_char C;
    
    C = (gen_chain_char)GetProcAddress(module, "gen_chain_char");

    int sum  = C(words, len, result, headChar, tailChar, rejectChar, enable_loop);
    return sum;
}
#endif // INPUT


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

bool isTxT(char* str) {
    int length = strlen(str);
    return !(length < 4 || str[length - 4] != '.'
        || str[length - 3] != 't'
        || str[length - 2] != 'x'
        || str[length - 1] != 't');
}

int readCommand(int argc, char *argv[], char **wordsR[], int *len, char *errMessage) {
    for (int i = 1; i < argc - 1; i++) {
        //if (argv[i] == "-n") {
        if (strcmp(argv[i], "-n") == 0) {
            if (option == Option::DEFAULT && tail == 0 && head == 0 && !isRing) {
                option = Option::N_ALL_CHAIN;
            } else {
                //handleException(CONFLICT_OP, "-n");
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-n"));
                return CONFLICT_OP;
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (option == Option::DEFAULT) {
                option = Option::C_MAX;
            } else {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-c"));
                return CONFLICT_OP;
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            if (option == Option::DEFAULT) {
                option = Option::W_MAX;
            } else {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-w"));
                return CONFLICT_OP;
            }
        } else if (strcmp(argv[i], "-j") == 0) {
            int r;
            if (reject != 0) {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-j"));
                return CONFLICT_OP;
            } else if ((r = isChar(argv[i + 1])) != 0) {
                if (r == -1 && !isTxT(argv[i + 1])) {
                    strcpy_s(errMessage, MAX_LENGTH, handleException(J_LONG_ALPHA, argv[i + 1]));
                    return J_LONG_ALPHA;
                } else {
                    strcpy_s(errMessage, MAX_LENGTH, handleException(J_NO_ALPHA, "str"));
                    return J_NO_ALPHA;
                }
            } else if (option == Option::N_ALL_CHAIN) {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-j"));
                return CONFLICT_OP;
            } else {
                reject = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            int r;
            if (head != 0) {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-h"));
                return CONFLICT_OP;
            } else if ((r = isChar(argv[i + 1])) != 0) {
                
                if (r == -1 && !isTxT(argv[i+1])) {
                    strcpy_s(errMessage, MAX_LENGTH, handleException(H_LONG_ALPHA, argv[i + 1]));
                    return H_LONG_ALPHA;
                } else {
                    strcpy_s(errMessage, MAX_LENGTH, handleException(H_NO_ALPHA, "str"));
                    return H_NO_ALPHA;
                }
            } else if (option == Option::N_ALL_CHAIN) {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-h"));
                return CONFLICT_OP;
            } else {
                head = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            int r;
            if (tail != 0) {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-t"));
                return CONFLICT_OP;
            } else if ((r = isChar(argv[i + 1])) != 0) {
                if (r == -1 && !isTxT(argv[i + 1])) {
                    strcpy_s(errMessage, MAX_LENGTH, handleException(T_LONG_ALPHA, argv[i + 1]));
                    return T_LONG_ALPHA;
                } else {
                    strcpy_s(errMessage, MAX_LENGTH, handleException(T_NO_ALPHA, "str"));
                    return T_NO_ALPHA;
                }
            } else if (option == Option::N_ALL_CHAIN) {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-t"));
                return CONFLICT_OP;
            } else {
                tail = argv[++i][0];
            }
        } else if (strcmp(argv[i], "-r") == 0) {
            int r;
            if (option == Option::N_ALL_CHAIN) {
                strcpy_s(errMessage, MAX_LENGTH, handleException(CONFLICT_OP, "-r"));
                return CONFLICT_OP;
            }
            isRing = true;
        } else {
            //handleExceptionWithExit(UNKNOWN_OP, argv[i]);
            strcpy_s(errMessage, MAX_LENGTH, handleException(UNKNOWN_OP, argv[i]));
                return UNKNOWN_OP;
        }
    }
    int length = (int) strlen(argv[argc - 1]);
    if (length <= 4 || argv[argc - 1][length - 4] != '.'
        || argv[argc - 1][length - 3] != 't'
        || argv[argc - 1][length - 2] != 'x'
        || argv[argc - 1][length - 1] != 't') {
        strcpy_s(errMessage, MAX_LENGTH, handleException(NOT_TXT, argv[argc - 1]));
        return NOT_TXT;
    }
    static vector<char *> words;
    string filename = argv[argc - 1];
    ifstream fin(filename.c_str(), ios::in | ios::binary | ios::ate);
    if (fin.is_open()) {
        static ios::pos_type size = fin.tellg();
        static string raw_input(size, 0);
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
            strcpy_s(errMessage, MAX_LENGTH, handleException(NO_WORDS, argv[argc - 1]));
            return NO_WORDS;
        }
    } else {
        strcpy_s(errMessage, MAX_LENGTH, handleException(OPEN_FAILED, argv[argc - 1]));
        return OPEN_FAILED;
    }
    *len = (int) words.size();
    *wordsR = words.data();
    fin.close();
    return 0;
}

void outPut(char *result[], int len, string outputFileName, Option op) {
    ofstream outFile(outputFileName);
    if (outFile.is_open()) {
        if (op == Option::N_ALL_CHAIN) {
            cout << len << endl;
            outFile << len << endl;
        }
        for (int i = 0; i < len; i++) {
            cout << result[i] << endl;
            outFile << result[i] << endl;
        }
    } else {
        cerr << "Failed to open output file" << endl;
    }
}

static char buffer[MAX_NUM][MAX_LENGTH];
// option 处理文件 以及 报错
int main_serve(int argc, char *argv[]) {
    char **words[MAX_LENGTH];
    char errMessage[MAX_LENGTH];

    int len;
    int readRet;
    readRet = readCommand(argc, argv, words, &len, errMessage);
    if (readRet < 0) {
        cerr << errMessage << endl;
        return readRet;
    }
    
    char *results[MAX_NUM];
    for (int i = 0; i < MAX_NUM; i++) {
        results[i] = buffer[i];
    }
    int ret;

    try {
        switch (option) {
            case Option::N_ALL_CHAIN:
                #ifdef INPUT
                ret = DynamicUseN(*words, len, results);
                #else
                ret = Core::gen_chains_all(*words, len, results);
                #endif
                break;
            case Option::W_MAX:
                #ifdef INPUT
                ret = DynamicUseW(*words, len, results, head, tail, reject,
                                  isRing);
                #else
                ret = Core::gen_chain_word(*words, len, results, head, tail, reject,
                                           isRing);
                #endif
                break;
            case Option::C_MAX:
                #ifdef INPUT
                ret = DynamicUseC(*words, len, results, head, tail, reject,
                                  isRing);
                #else
                ret = Core::gen_chain_char(*words, len, results, head, tail, reject,
                                           isRing);
                #endif

                break;
            default:
                cerr << handleException(LACK_COMMAND, "") << endl;
                return LACK_COMMAND;
        }
    } catch (runtime_error const &e) {
        throw e;
    }
    outPut(results, ret, "solution.txt", option);
    return 0;
}

int main(int argc, char *argv[]) {
        try {
        main_serve(argc, argv);
    } catch (runtime_error const &e) {
        cerr << "Invalid input: " << e.what() << endl;
    }
    return 0;
}