#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "indexOp.h"

static Records rec;
static pthread_mutex_t mutex;

void *removefile(void *filenameptr){
    const char *filename = (const char *)filenameptr;

    RecordPtr recptr = getPtrOfDocxitRecord(rec, filename);

    if(recptr == NULL || isRecordKind(recptr, removed)){     // cannot find
        pthread_exit(&rec);     // failed
    }

    if(isRecordKind(recptr, unchanged) || isRecordKind(recptr, changed)){
        pthread_mutex_lock(&mutex);
        setRecordKind(recptr, removed);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }

    // add type, just remove
    pthread_mutex_lock(&mutex);
    deleteDocxitRecordByPtr(recptr);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("nothing is removed\n");
        exit(0);
    }

    rec = openIndex(INDEX_FILE_NAME);       // get record array

    pthread_mutex_init(&mutex, NULL);       // init mutex lock

    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * (argc - 1));

    int i;
    for(i = 2; i < argc; i ++){
        if(pthread_create(&threads[i - 2], NULL, removefile, argv[i])){
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
        if(!ret) printf("remove %s\n", argv[i]);
        else printf("%s: cannot find file\n", argv[i]);
    }

    char path[4096] = {'\0'};
    strcat(path, argv[1]);
    strcat(path, ".docxit/");
    strcat(path, INDEX_FILE_NAME);
    writeRecordsToFile(INDEX_FILE_NAME, rec);

    free(threads);
    return 0;
}
