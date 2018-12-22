#include "getBranch.h"

string getCurrentBranch(string path){

    // get current branch
    string curbr = "cat ";
    curbr = curbr + path + ".docxit/HEAD";
    curbr = shellCommand(curbr);
    curbr = curbr.substr(curbr.rfind('/') + 1);

    return curbr;
}

string getCurrentCommitKey(string path){
    string curbr = "cat `cat ";
    curbr = curbr + path + ".docxit/HEAD`";
    curbr = shellCommand(curbr);
    return curbr;
}

void resetCurrentBranch(string newkey, string path){
    string curbr = "echo -n " + newkey + ">`cat ";
    curbr = curbr + path + ".docxit/HEAD`";
    if(system(curbr.c_str()) == -1){
        printf("fatal: %s: cannot execute\n", curbr.c_str());
        exit(0);
    }
}

void printCurrentBranch(const char *path){
    printf("On branch %s\n", getCurrentBranch(path).c_str());
}
