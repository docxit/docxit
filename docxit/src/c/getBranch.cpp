#include "getBranch.h"

string getCurrentBranch(string path){

    // get current branch
    string curbr = "cat ";
    curbr = curbr + path + ".docxit/HEAD";
    curbr = shellCommand(curbr);
    curbr = curbr.substr(curbr.rfind('/') + 1);

    return curbr;
}

void printCurrentBranch(const char *path){
    printf("On branch %s\n", getCurrentBranch(path).c_str());
}
