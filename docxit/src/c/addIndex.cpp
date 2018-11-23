#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "indexOp.h"
#include "sha1.h"
#include "blobCreate.h"

static Records rec;
static pthread_mutex_t mutex;

static void *addfile(void *filenameptr){
    string filename = (const char *)filenameptr;
    const char *cfilename = (const char *)filenameptr;
    string sha1 = valueSHA_1(filename);
    const char *ckey = sha1.c_str();

    blobCreate(filename, sha1);
    RecordPtr recptr = getPtrOfDocxitRecord(rec, cfilename);

    if(recptr == NULL){     // not found
        DocxitRecord dc;
        setRecordKind(&dc, add);
        setRecordName(&dc, cfilename);
        setRecordKey(&dc, ckey);
        setRecordNewkey(&dc, "");

        pthread_mutex_lock(&mutex);
        insertDocxitRecord(&rec, dc);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }

    if(isRecordKey(recptr, ckey)){      // key not change
        if(isRecordKind(recptr, removed)){  // removed
            pthread_mutex_lock(&mutex);
            setRecordKind(recptr, unchanged);
            pthread_mutex_unlock(&mutex);
        }
        pthread_exit(NULL);
    }

    if(isRecordKind(recptr, removed) || isRecordKind(recptr, unchanged)){      // key changed
        pthread_mutex_lock(&mutex);
        setRecordKind(recptr, changed);
        setRecordNewkey(recptr, ckey);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }

    if(isRecordKind(recptr, add)){
        pthread_mutex_lock(&mutex);
        setRecordKey(recptr, ckey);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }

    if(isRecordKey(recptr, ckey)){      // changed -> unchanged
        pthread_mutex_lock(&mutex);
        setRecordKind(recptr, unchanged);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }

    //changed -> changed
    pthread_mutex_lock(&mutex);
    setRecordNewkey(recptr, ckey);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("nothing is added\n");
        exit(0);
    }

    rec = openIndex(INDEX_FILE_NAME);       // get record array

    pthread_mutex_init(&mutex, NULL);       // init mutex lock

    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * (argc - 1));   // init threads

    int i;
    for(i = 2; i < argc; i ++){
        if(pthread_create(&threads[i - 2], NULL, addfile, argv[i])){
            printf("fatal error: %s: cannot create thread\n", argv[i]);
            exit(0);
        }
    }


    for(i = 2; i < argc; i ++){
        void *ret = NULL;
        if(pthread_join(threads[i - 2], &ret)){
            printf("fatal error: %s: cannot join with thread\n", argv[i]);
            exit(0);
        }
        printf("add %s\n", argv[i]);
    }

    char path[4096] = {'\0'};
    strcat(path, argv[1]);
    strcat(path, ".docxit/");
    strcat(path, INDEX_FILE_NAME);
    writeRecordsToFile(INDEX_FILE_NAME, rec);

    freeRecords(&rec);
    free(threads);
    return 0;
}
