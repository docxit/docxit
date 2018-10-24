#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *usage = "\
Usage: docxit [--version] [--help] <command> [<args>]\n\
\
";
    const char *version = "docxit version 1.0.0\n";

    if(argc <= 1){
        printf("%s", usage);
        exit(0);
	}

	if(!strcmp(argv[1], "--help")){
        printf("%s", usage);
	}
	else if(!strcmp(argv[1], "--version")){
        printf("%s", version);
	}
	else if(!strcmp(argv[1], "add")){

	}
	else if(!strcmp(argv[1], "commit")){

	}
	else if(!strcmp(argv[1], "diff")){

	}
	else if(!strcmp(argv[1], "help")){
        printf("%s", usage);
	}
	else if(!strcmp(argv[1], "init")){

	}
	else if(!strcmp(argv[1], "log")){

	}
	else if(!strcmp(argv[1], "reset")){

	}
	else if(!strcmp(argv[1], "status")){

	}
    else if(!strcmp(argv[1], "tag")){

	}
	else if(!strcmp(argv[1], "version")){
        printf("%s", version);
	}
	else{
        printf("unknown option: %s\n", argv[1]);
	}

	return 0;
}
