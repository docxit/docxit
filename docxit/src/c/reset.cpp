#include "switchVersion.h"
#include "indexOp.h"
#include "getBranch.h"

#define RESETHELP "\
Usage:  docxit reset                    reset to latest commited version\
        docxit reset prev [<number>]    reset backward number times (1 by default)\
        docxit reset <commit_key>       reset to specific commited version\
"

int main(int argc, char *argv[]){
    printCurrentBranch(argv[1]);
    if(argc == 2){
        string key = getCurrentCommitKey(argv[1]);
        changeIndex(key.c_str(), argv[1]);
        switchVersion(argv[1]);
        resetCurrentBranch(key, argv[1]);
        printf("Successfully reset to latest commited version %s\n", key.c_str(););
    }
    else if(!strcmp(argv[2], "prev")){
        int n = 1;
        if(argc >= 4) n = strtol(argv[3], NULL, 10);
        string key = getCurrentCommitKey(argv[1]);
        key = changePrevIndex(key, argv[1], n);
        switchVersion(argv[1]);
        resetCurrentBranch(key, argv[1]);
        printf("Successfully reset %d times backwrad to version %s\n", n, key.c_str());
    }
    else if(argc == 3 && *argv[2] != '-'){
        changeIndex(argv[2], argv[1]);
        switchVersion(argv[1]);
        resetCurrentBranch(argv[2], argv[1]);
        printf("Successfully reset to commited version %s\n", argv[2]);
    }
    else printf("%s\n", RESETHELP);
}
