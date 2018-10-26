#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "docxitPath.h"

#define EXE_DIR "/usr/local/lib/docxit/"

int main(int argc, char *argv[])
{
    //TODO: alias

    const char *usage = "\
Usage: docxit [--version] [--help] <command> [<args>]\n\
\
";
    const char *version = "docxit version 1.0.0\n";

    if(argc <= 1){
        printf("%s", usage);
        exit(0);
	}

    if(!strcmp(argv[1], "init")){
        if(docxitPath())
            printf("Nested initialization not supported\n");
        else if(execv(EXE_DIR"init", argv) == -1)
            perror(EXE_DIR"init");
        return 0;
	}

	if(!docxitPath()){
        printf("fatal: not a docxit repository\n");
        return 0;
    }
    argv[0] = (char *)DOCXIT_PATH.c_str();

	if(!strcmp(argv[1], "--help")){
        printf("%s", usage);
	}
	else if(!strcmp(argv[1], "--version")){
        printf("%s", version);
	}
	else if(!strcmp(argv[1], "add")){
        if(execv(EXE_DIR"add", argv) == -1)
            perror(EXE_DIR"add");
	}
	else if(!strcmp(argv[1], "commit")){
        if(execv(EXE_DIR"commit", argv) == -1)
            perror(EXE_DIR"commit");
	}
	else if(!strcmp(argv[1], "diff")){
        if(execv(EXE_DIR"diff", argv) == -1)
            perror(EXE_DIR"diff");
	}
	else if(!strcmp(argv[1], "help")){
        printf("%s", usage);
	}
	else if(!strcmp(argv[1], "log")){
        if(execv(EXE_DIR"log", argv) == -1)
            perror(EXE_DIR"log");
	}
	else if(!strcmp(argv[1], "reset")){
        if(execv(EXE_DIR"reset", argv) == -1)
            perror(EXE_DIR"reset");
	}
	else if(!strcmp(argv[1], "status")){
        if(execv(EXE_DIR"status", argv) == -1)
            perror(EXE_DIR"status");
	}
    else if(!strcmp(argv[1], "tag")){
        if(execv(EXE_DIR"tag", argv) == -1)
            perror(EXE_DIR"tag");
	}
	else if(!strcmp(argv[1], "version")){
        printf("%s", version);
	}
	else{
        printf("unknown option: %s\n%s", argv[1], usage);
	}

	return 0;
}
