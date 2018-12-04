#include<stdio.h>
#include<stdlib.h>
#include "commitTree.h"

int main(int argc, char *argv[])
{
    string inst = "cat `cat ";
    inst = inst + argv[1] + ".docxit/HEAD`";
    string key = shellCommand(inst);
    if(key == "null"){
        printf("no commit in current branch\n");
    }
    else{
        printCommitTree(key.c_str(), argv[1]);
    }
    return 0;
}

