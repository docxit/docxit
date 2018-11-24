#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSTRUCTION_MAX_LENGTH 4096

int main(int argc, char *argv[]){
// argv: docxit, <docxitPath>

    if(argc <= 1) return -1;
    printf("WARNING: version information cannot be restored after deletion. \nPress Y to continue (Y / N) (default N): ");
    fflush(stdin);
    int c = getchar();

    if(c == 'y' || c == 'Y'){
        char inst[INSTRUCTION_MAX_LENGTH] = "rm -rf ";
        strcat(inst, argv[1]);
        strcat(inst, ".docxit/");
        if(!inst[INSTRUCTION_MAX_LENGTH - 1]) {  // not overflow
            if(system(inst) == -1){
                printf("fatal: %s: cannot execute\n", inst);
                exit(0);
            }
            printf("Successfully deinit Docxit repository\n");
        }
        else printf("fatal error: %s: name too long\n", argv[1]);
    }
    else{
        printf("deletion aborted\n");
    }
}

