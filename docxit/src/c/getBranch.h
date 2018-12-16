#ifndef __GET_BRANCH_H__
#define __GET_BRANCH_H__

#include "shellCommand.h"

string getCurrentBranch(string path);  // return current branch

string getCurrentCommitKey(string path);

void resetCurrentBranch(string newkey, string path);

void printCurrentBranch(const char *path);

#endif
