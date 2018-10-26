#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "docxitPath.h"

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
            printf("nested initialization not supported\n");
        else if(execl("/usr/local/lib/docxit/init", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/init\n");
        return 0;
	}

	if(!docxitPath()){
        printf("fatal: not a docxit repository\n");
        return 0;
    }

	if(!strcmp(argv[1], "--help")){
        printf("%s", usage);
	}
	else if(!strcmp(argv[1], "--version")){
        printf("%s", version);
	}
	else if(!strcmp(argv[1], "add")){
        if(execl("/usr/local/lib/docxit/add", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/add\n");
	}
	else if(!strcmp(argv[1], "commit")){
        if(execl("/usr/local/lib/docxit/commit", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/commit\n");
	}
	else if(!strcmp(argv[1], "diff")){
        if(execl("/usr/local/lib/docxit/diff", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/diff\n");
	}
	else if(!strcmp(argv[1], "help")){
        printf("%s", usage);
	}
	else if(!strcmp(argv[1], "log")){
        if(execl("/usr/local/lib/docxit/log", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/log\n");
	}
	else if(!strcmp(argv[1], "reset")){
        if(execl("/usr/local/lib/docxit/reset", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/reset\n");
	}
	else if(!strcmp(argv[1], "status")){
        if(execl("/usr/local/lib/docxit/status", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/status\n");
	}
    else if(!strcmp(argv[1], "tag")){
        if(execl("/usr/local/lib/docxit/tag", NULL) == -1)
            printf("fatal: cannot find /usr/local/lib/docxit/tag\n");
	}
	else if(!strcmp(argv[1], "version")){
        printf("%s", version);
	}
	else{
        printf("unknown option: %s\n%s", argv[1], usage);
	}

	return 0;
}
