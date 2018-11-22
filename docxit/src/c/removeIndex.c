#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexOp.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("nothing is removed\n");
        exit(0);
    }

    int i;
    for(i = 1; i < argc; i ++){
        const char *filename = argv[i];

        // replace this printf with function implemention
        printf("remove %s\n", filename);

    }

    return 0;
}
