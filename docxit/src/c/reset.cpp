#include "switchVersion.h"
#include "indexOp.h"
#include "getBranch.h"
#include "commitTree.h"

#define RESETHELP "\
Usage:  docxit reset                    reset to latest committed version\n\
        docxit reset prev [<number>]    reset backward number times (1 by default)\n\
        docxit reset <commit_key>       reset to specific committed version\n\
\n\
Warning: make sure you have committed your changeds before executing reset, or they will be lost\
"

int main(int argc, char *argv[]){
    printCurrentBranch(argv[1]);
    string str = shellCommand("pwd");
    if(argc == 2){
        if(str.substr(0, str.length() - 1) + "/" != argv[1]){
            printf("error: please execute reset in repository root `%s`\n", argv[1]);
            //exit(0);
        }
        string key = getCurrentCommitKey(argv[1]);
        changeIndex(key.c_str(), argv[1]);
        switchVersion(argv[1], key);
        printf("Successfully reset to latest committed version %s\n", key.c_str());
    }
    else if(!strcmp(argv[2], "prev")){
        if(str.substr(0, str.length() - 1) + "/" != argv[1]){
            printf("error: please execute reset in `%s`\n", argv[1]);
            exit(0);
        }
        int n = 1;
        if(argc >= 4) n = strtol(argv[3], NULL, 10);
        string key = getCurrentCommitKey(argv[1]);
        key = changePrevIndex(key.c_str(), argv[1], n);
        switchVersion(argv[1], key);
        printf("Successfully reset %d times backwrad to version %s\n", n, key.c_str());
    }
    else if(argc == 3 && *argv[2] != '-'){
        if(str.substr(0, str.length() - 1) + "/" != argv[1]){
            printf("error: please execute reset in `%s`\n", argv[1]);
            exit(0);
        }
        changeIndex(argv[2], argv[1]);
        switchVersion(argv[1], argv[2]);
        printf("Successfully reset to committed version %s\n", argv[2]);
    }
    else printf("%s\n", RESETHELP);
}
