#ifndef __MERGEOP_H__
#define __MERGEOP_H__

#include<iostream>
#include<fstream>
#include<string>
#include"commitTree.h"
#include"shellCommand.h"

using namespace std;

string indexKey(const char *branchname, const char *docxitpath);

int isBranch(const char *branchname, const char *docxitpath);

string branchKey(const char *branchname, const char *docxitpath);

CommitStruct *csCommitkey(const char *commitkey, const char *docxitpath);

string getHeadBranch(const char *docxitpath);

int isInSameBranch(const char *pbranch, const char *cbranch, const char *docxitpath);

void changBranchKey(const char *tobranchname, const char *frombranchname, const char *docxitpath);

#endif // __MERGEOP_H__
