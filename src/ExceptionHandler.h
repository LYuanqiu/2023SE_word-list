//
// Created by 12740 on 3/13/2023.
//

#ifndef INC_2023SE_WORD_LIST_EXCEPTIONHANDLER_H
#define INC_2023SE_WORD_LIST_EXCEPTIONHANDLER_H

#define UNKNOWN_OP (-1)
#define CONFLICT_OP (-2)
#define NO_SUCH_FILE (-3)
#define NOT_TXT (-4)
#define OPEN_FAILED (-5)
#define NO_WORDS (-6)
#define FAIL_OUTPUT (-7)
#define MISSING_FILE (-8)
#define H_NO_ALPHA (-9)
#define T_NO_ALPHA (-10)
#define J_NO_ALPHA (-11)
#define H_LONG_ALPHA (-12)
#define T_LONG_ALPHA (-13)
#define J_LONG_ALPHA (-14)
#define NOT_ARG (-15)
#define MISSING_ARG (-16)
#define NO_CHAIN (-17)
#define HAS_RING (-18)
#define LACK_COMMAND (-19)

char* handleException(int error, const char* arg){
    static string errMessage;
    switch (error) {
        case UNKNOWN_OP:
            errMessage = "Missing functional parameters, option not found!";
            break;
        case CONFLICT_OP:
            errMessage =  "Conflict parameters!";
            break;
        case NO_SUCH_FILE:
            errMessage =  "Can not find " + (string)arg + "!";
            break;
        case NOT_TXT:
            errMessage =  (string)arg + " not a txt file!";
            break;
        case OPEN_FAILED:
            errMessage =  "Failed to open " + (string)arg  +"!";
            break;
        case NO_WORDS:
            errMessage =  "No words in "+(string)arg +"!";
            break;
        case FAIL_OUTPUT:
            errMessage =  "Failed to open output file!";
            break;
        case MISSING_FILE:
            errMessage =  "Missing file name!" ;
            break;
        case H_NO_ALPHA:
            errMessage =  "Parameter '-h' needs a alpha!" ;
            break;
        case T_NO_ALPHA:
            errMessage =  "Parameter '-t' needs a alpha!" ;
            break;
        case J_NO_ALPHA:
            errMessage =  "Parameter '-j' needs a alpha!" ;
            break;
        case H_LONG_ALPHA:
            errMessage =  "Parameter '-h' only needs one alpha!" ;
            break;
        case T_LONG_ALPHA:
            errMessage =  "Parameter '-t' only needs one alpha!" ;
            break;
        case J_LONG_ALPHA:
            errMessage =  "Parameter '-j' only needs one alpha!" ;
            break;
        case NOT_ARG:
            errMessage =  (string)arg + " is not a parameter!" ;
            break;
        case MISSING_ARG:
            errMessage = "Missing arguments!";
            break;
        case NO_CHAIN:
            errMessage = "There is no chain in the file!";
            break;
        case HAS_RING:
            errMessage = "There are rings in the file!";
            break;
        case LACK_COMMAND:
            errMessage = "Lack functional Command!";
        default:
            errMessage =  "Unexpected error!" ;
            break;
    }
    return &errMessage[0];
}

void handleExceptionWithExit(int errcode,const char* arg){
    cerr << handleException(errcode, arg) << endl;
    exit(0);
}

#endif //INC_2023SE_WORD_LIST_EXCEPTIONHANDLER_H
