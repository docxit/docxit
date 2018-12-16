#include<iostream>
#include"mergeOp.h"

#define USAGE "\
Usage: docxit merge -m \"<merge_message>\" branchname\n\
"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 5)
    {
        cout << USAGE;
        return 0;
    }
    if(strcmp(argv[2], "-m") != 0)
    {
        cout << USAGE;
        return 0;
    }
    string merge_message = argv[3];
    if(isBranch(argv[4], argv[1]) == 0)
    {
        cout << "there is no branch " << argv[4] << endl;
    }
    string branchname = getHeadBranch(argv[1]);
    int res = isInSameBranch(branchname.c_str(), argv[4], argv[1]);
    if(res == 1)
    {
        changBranchKey(branchname.c_str(), argv[4], argv[1]);
    }
    else if(res == 2)
    {

    }
    else
    {

    }
}
