#include<stdio.h>
#include<stdlib.h>
#include "commitTree.h"

int main(int argc, char *argv[])
{
    string inst = "cat `cat ";
    inst = inst + argv[1] + ".docxit/HEAD`";
    string key = shellCommand(inst);

    // get current branch
    string curbr = "cat ";
    curbr = curbr + argv[1] + ".docxit/HEAD";
    curbr = shellCommand(curbr);
    curbr = curbr.substr(curbr.rfind('/') + 1);

    if(key == "null"){
        printf("no commit in current branch\n");
    }
    else{
        printCommitTree(key.c_str(), argv[1], curbr.c_str());
    }
    return 0;
}

