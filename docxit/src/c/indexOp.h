#ifndef __INDEX_OP_H__
#define __INDEX_OP_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define RECORDS_INIT_SIZE 50
#define RECORDS_INCREMENT 10
#define MAX_NAME_LENGTH 256
#define INDEX_FILE_NAME "index"

typedef enum{
    add, removed, changed, unchanged, nonexisting
}DocxitRecordKind;

typedef struct{
    DocxitRecordKind kind;
    char name[MAX_NAME_LENGTH];
    char key[41];
    char newkey[41];
}DocxitRecord, *RecordPtr;

typedef struct{
    RecordPtr base;
    long length;
    long recordSize;
}Records;

static inline void setRecordKind(RecordPtr ptr, DocxitRecordKind kind){
    ptr -> kind = kind;
}

static inline void setRecordName(RecordPtr ptr, const char *name){
    strcpy(ptr -> name, name);
}

static inline void setRecordKey(RecordPtr ptr, const char *key){
    strcpy(ptr -> key, key);
}

static inline void setRecordNewkey(RecordPtr ptr, const char *newkey){
    strcpy(ptr -> newkey, newkey);
}

static inline DocxitRecordKind getRecordKind(RecordPtr ptr){
    return ptr -> kind;
}

static inline const char * getRecordName(RecordPtr ptr){
    return ptr -> name;
}

static inline const char * getRecordKey(RecordPtr ptr){
    return ptr -> key;
}

static inline const char * getRecordNewkey(RecordPtr ptr){
    return ptr -> newkey;
}

static inline int isRecordKind(RecordPtr ptr, DocxitRecordKind kind){
    return ptr -> kind == kind;
}

static inline int isRecordName(RecordPtr ptr, const char *name){
    return !strcmp(ptr -> name, name);
}

static inline int isRecordKey(RecordPtr ptr, const char *key){
    return !strcmp(ptr -> key, key);
}

static inline int isRecordNewkey(RecordPtr ptr, const char *newkey){
    return !strcmp(ptr -> newkey, newkey);
}


Records openIndex(const char *indexFileName);

void freeRecords(Records *rec);

RecordPtr getPtrOfDocxitRecord(Records rec, const char *name);
// succeed return the pointer of the record
// failed return NULL

void insertDocxitRecord(Records *rec, DocxitRecord insrec);

static void setRecordKind(RecordPtr ptr, DocxitRecordKind kind);

static void setRecordName(RecordPtr ptr, const char *name);

static void setRecordKey(RecordPtr ptr, const char *key);

static void setRecordNewkey(RecordPtr ptr, const char *newkey);

static DocxitRecordKind getRecordKind(RecordPtr ptr);

static const char * getRecordName(RecordPtr ptr);

static const char * getRecordKey(RecordPtr ptr);

static const char * getRecordNewkey(RecordPtr ptr);

static int isRecordKind(RecordPtr ptr, DocxitRecordKind kind);

static int isRecordName(RecordPtr ptr, const char *name);

static int isRecordKey(RecordPtr ptr, const char *key);

static int isRecordNewkey(RecordPtr ptr, const char *newkey);

void deleteDocxitRecordByPtr(RecordPtr ptr);

void writeRecordsToFile(const char *indexFileName, Records rec);

int printStatus(Records rec);   // 0: all unchanged

int commitIndex(const char *indexFileName);

#ifdef DEBUG
void printRecords(Records rec);
#endif // DEBUG

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
