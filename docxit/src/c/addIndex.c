#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexOp.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("fatal error: argc error in addIndex.c\n");
        exit(0);
    }

    const char *filename = argv[1];

    // replace this printf with function implemention
    printf("add %s\n", filename);

    return 0;
}
