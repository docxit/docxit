#ifndef __MERGEOP_H__
#define __MERGEOP_H__

#include<iostream>
#include<fstream>
#include<string>
#include"commitTree.h"
#include"shellCommand.h"

using namespace std;

int isBranch(const char *branchname, const char *docxitpath);

string getHeadBranch(const char *docxitpath);

int isInSameBranch(const char *pbranch, const char *cbranch, const char *docxitpath);

void changCurBranchKey(const char *branchname);

#endif // __MERGEOP_H__
