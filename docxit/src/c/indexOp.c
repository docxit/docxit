#include "indexOp.h"

static inline long getInitSize(long fileSize){
    if(fileSize < RECORDS_INIT_SIZE) return RECORDS_INIT_SIZE;
    else return ((fileSize - RECORDS_INIT_SIZE) / RECORDS_INCREMENT + 1) * RECORDS_INCREMENT + RECORDS_INIT_SIZE;
}

Records openIndex(const char *indexFileName){
    FILE *fp = fopen(indexFileName, "a+b");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", indexFileName);
        exit(0);
    }

    fseek(fp, 0L, SEEK_END);
    long fileSize = ftell(fp) / sizeof(DocxitRecord);
    fseek(fp, 0L, SEEK_SET);
    fseek(fp, 0L, SEEK_SET);

    long recInitSize = getInitSize(fileSize);
    Records rec = {NULL, fileSize, recInitSize};
    void *p = malloc(recInitSize * sizeof(DocxitRecord));
    if(!p){
        printf("fatal error: malloc failed\n");
        exit(0);
    }
    fread(p, sizeof(DocxitRecord), fileSize, fp);
    rec.base = (RecordPtr)p;

    fclose(fp);
    return rec;
}

void freeRecords(Records *rec){
    if(rec -> base)free(rec -> base);
    rec -> base = NULL;
    rec -> length = 0;
    rec -> recordSize = 0;
}

RecordPtr getPtrOfDocxitRecord(Records rec, const char *name){
    long i;
    for(i = 0; i < rec.length; i ++){
        if(!strcmp(rec.base[i].name, name)){
            if(rec.base[i].kind == nonexisting) return NULL;
            else return &rec.base[i];
        }
    }
    return NULL;
}

void insertDocxitRecord(Records *rec, DocxitRecord insrec/*const DocxitRecord *insRecPtr*/){
    if(rec -> length == rec -> recordSize){
        void *p = realloc(rec -> base, (rec -> recordSize + RECORDS_INCREMENT) * sizeof(DocxitRecord));
        if(!p){
            printf("fatal error: realloc failed\n");
            exit(0);
        }
        rec -> base = (RecordPtr)p;
        rec -> recordSize += RECORDS_INCREMENT;
    }
    //rec -> base[rec -> length ++] = *insRecPtr;
    rec -> base[rec -> length ++] = insrec;
}

void deleteDocxitRecordByPtr(RecordPtr ptr){
    ptr -> kind = nonexisting;
}

void writeRecordsToFile(const char *indexFileName, Records rec){
    FILE *fp = fopen(indexFileName, "wb");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", indexFileName);
        exit(0);
    }

    int i;
    for(i = 0; i < rec.length; i ++){
        if(rec.base[i].kind != nonexisting){
            fwrite(rec.base + i, sizeof(DocxitRecord), 1L, fp);
        }
    }

    fclose(fp);
}

int commitIndex(const char *indexFileName){
// 0 clear, 1 have changed
    Records rec = openIndex(indexFileName);

    int i, ret = 0;
    for(i = 0; i < rec.length; i ++){
        if(rec.base[i].kind != unchanged){
            ret = 1;
            if(isRecordKind(&rec.base[i], changed)){
                setRecordKey(&rec.base[i], getRecordNewkey(&rec.base[i]));
            }
            if(isRecordKind(&rec.base[i], removed)){
                deleteDocxitRecordByPtr(&rec.base[i]);
                continue;
            }
            setRecordNewkey(&rec.base[i], "");
            setRecordKind(&rec.base[i], unchanged);
        }
    }

    if(ret) writeRecordsToFile(indexFileName, rec);
    freeRecords(&rec);

    return ret;
}

#ifdef DEBUG
void printRecords(Records rec){
    printf("legnth: %ld, size: %ld\n", rec.length, rec.recordSize);
    int i;
    for(i = 0; i < rec.length; i ++){
        switch(rec.base[i].kind){
            case add: printf("add\t"); break;
            case removed: printf("removed\t"); break;
            case changed: printf("changed\t"); break;
            case unchanged: printf("unchanged\t"); break;
            case nonexisting: continue;
            default: break;
        }
        printf("%s\t%s\t%s\n", rec.base[i].name, rec.base[i].key, rec.base[i].newkey);
    }

}
#endif
