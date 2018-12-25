#include<iostream>
#include"mergeOp.h"
#include"commitTree.h"
#include"switchVersion.h"

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
        return 0;
    }
    string branchname = getHeadBranch(argv[1]);
    int res = isInSameBranch(branchname.c_str(), argv[4], argv[1]);
    //cout << "res = " << res << endl;
    if(res == 1)
    {
        //cout << branchname << "  " << argv[4] << endl;
        changBranchKey(branchname.c_str(), argv[4], argv[1]);
        string key = branchKey(branchname.c_str(), argv[1]);
        changeIndex(key.c_str(), argv[1]);
        switchVersion(argv[1], key);
        cout << "fast forward merge " << argv[4] << " successfully" << endl;
    }
    else if(res == 2)
    {
        cout << "fast forward merge " << argv[4] << " successfully" << endl;
    }
    else
    {
        cout << "not ff" << endl;
        string targetIndex = argv[1];
        targetIndex += ".docxit/index";
        string key = indexKey(branchname.c_str(), argv[1]);
        string sourceIndex = argv[1];
        sourceIndex += ".docxit/object/";
        key = indexKey(argv[4], argv[1]);
        sourceIndex += key.substr(0,2) + "/" + key.substr(2,38);
        string targetBranchName = branchname;
        string sourceBranchName = argv[4];
        string path = argv[1];
        mergeRecords(targetIndex, sourceIndex, targetBranchName, sourceBranchName, path);
    }
}
