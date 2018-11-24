#include"commitTree.h"

CommitStruct *createCommitStruct(const char *key, const char *message)
{
    CommitStruct *cs = (CommitStruct *)malloc(sizeof(CommitStruct));
    //author is saved in file config
    time_t rawtime;
    struct tm *ptminfo;

    time(&rawtime);
    ptminfo = localtime(&rawtime);
    strcpy(cs->committime, asctime(ptminfo));
    //read time
    strcpy(cs->key, key);
    cs->parentnum = 0;
    cs->childnum = 0;
    strcpy(cs->commitmessage, message);
    return cs;
}
void writeCommitStructToFile(const CommitStruct *cf, const char *filename){
    FILE *fp = fopen(filename, "wb");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", filename);
        exit(0);
    }

    fwrite(cf, sizeof(CommitStruct), 1, fp);

    fclose(fp);
}

void freeCommitStruct(CommitStruct **cs){
    free(*cs);
    *cs = NULL;
}
void insertCommitObjectToTree(const char *key)
{
    printf("insert %s\n",key);
}

void printCommitObject(const char *key, const char *path)
{
    string keyvalue = key;
    string dir = path;
    dir = dir + ".docxit/object/" + keyvalue.substr(0,2) + '/' + keyvalue.substr(2,38);
    FILE *fp = fopen(dir.c_str(),"rb");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", dir.c_str());
        exit(0);
    }
    CommitStruct *buf = (CommitStruct *)malloc(sizeof(CommitStruct));
    fread(buf, sizeof(CommitStruct), 1, fp);
    printf("Author: \t%s\nData: \t%s\n\n%s\n",buf->author,buf->committime,buf->commitmessage);
    free(buf);
    fclose(fp);
}
