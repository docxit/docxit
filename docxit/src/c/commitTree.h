#ifndef __COMMITTREE_H__
#define __COMMITTREE_H__
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include"shellCommand.h"
#include "configOp.h"
#include <vector>

using namespace std;

typedef struct
{
    char key[41];
    char author[64];
    char committime[64];
    char commitmessage[256];
    char parentkey[2][41];
    char childkey[10][41];
    char parentnum;
    char childnum;
}CommitStruct;


//branch master is created while docxit init is executed
//root is created while docxit init is executed, inited with null
string changePrevIndex(const char *commitkey, const char *path, int n);

string changeNextIndex(const char *commitkey, const char *path, int n);

void changeIndex(const char *commitkey, const char *path);

CommitStruct *createCommitStruct(const char *key, const char *message);
//create a file that records commit key, author, commit time and commit message
//create the file's blob obj and return it's key value

void writeCommitStructToFile(const CommitStruct *cf, const char *filename);

void freeCommitStruct(CommitStruct **cs);

void insertCommitObjectToTree(const char *key, const char *path);
//open file current branch(save in file HEAD), pass the key to parent_key, open parent_key file and write key into it, open key file and write parent_key into it,
//change the key in current branch into key
//if root is null, change root into key, change the branch in HEAD into key

void printTree();
//open root dfs, post order travel, print tree
void printCommitObject(const char *key, const char *path);

void printCommitTree(const char *key, const char *path, const char *currentBranch);

#endif // COMMITTREE_H
