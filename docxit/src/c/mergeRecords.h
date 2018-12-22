#ifndef __MERGE_RECORDS_H__
#define __MERGE_RECORDS_H__

#include "indexOp.h"
#include "switchVersion.h"
#include <vector>

using namespace std;

void mergeRecords(string targetIndex, string sourceIndex, string targetBranchName, string sourceBranchName, string path);

#endif
