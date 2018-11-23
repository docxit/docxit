#include "commitTree.h"

void writeCommitStructToFile(const CommitFile *cf, const char *filename){
    FILE *fp = fopen(filename, "wb");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", filename);
        exit(0);
    }

    fwrite(cf, sizeof(CommitFile), 1, fp);

    fclose(fp);
}

void freeCommitStruct(CommitStruct **cs){
    free(*cs);
    *cs = NULL;
}
