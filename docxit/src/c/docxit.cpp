#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "docxitPath.h"
#include "configOp.h"

#define EXE_DIR "/usr/local/lib/docxit/"

static void checkName(){
    string username = getUserName(configpath());
    if(username == ""){
        printf("Please use `docxit config --myname <user_name>` to set your name first\n");
        exit(0);
    }
}

static void checkDocxitPath(char *argv[]){
    checkName();
	if(system(EXE_DIR"updateDocxitPath.sh") == -1){
        printf("fatal: %s: cannot execute file\n", "updateDocxitPath.sh");
        exit(0);
	}
    int isrepo = docxitPath();
	if(isrepo == 0 || isrepo == 2){
        printf("fatal: not a docxit repository\n");
        exit(0);
    }
    argv[1] = (char *)DOCXIT_PATH.c_str();
}

/// file name contains ' ' can't add !!!
/// checkout will rm all uncommited files
/// todo: status and other enough test, use doc to test, in child dir of repo
int main(int argc, char *argv[])
{
    //TODO: alias
#ifndef DEBUG
    const char *usage = "\
Usage: docxit [--version] [--help] <command> [<args>]\n\
\n\
commands:\n\
    add         docxit add <file1> [<file2> ...]            add or remove files to index\n\
    commit      docxit commit -m \"<commit_message>\"         commit changes to docxit\n\
    diff        docxit diff <filename1> [<filename2> ...]   show difference between filename and its latest version\n\
    listen      docxit listen                               get ready to receive\n\
    sendto      docxit sendto [-ip <ip> | <username>]       send current version to remote user\n\
    log         docxit log                                  show docxit commit log\n\
    status      docxit status                               show index and workspace status\n\
    branch      docxit branch [-d] <branch_name>            create or delete branches\n\
    config      docxit config [options <args>]              set docxit configuration\n\
    help        docxit help                                 show this help\n\
    merge       docxit merge -m \"<message>\" <branch_name>   merge two branches\n\
    tag         docxit tag \"<tag_name>\" [<commit_value>]    tag specific commit\n\
    checkout    docxit checkout [-b] <new_branch_name>      move to another branch\n\
    deinit      docxit deinit                               delete docxit repository\n\
    init        docxit init                                 init docxit repository at current directory\n\
    reset       docxit reset [options]                      reset workspace to specific version\n\
    version     docxit version                              show docxit version info\n\
\n\
\
";
#else
    const char *usage = "\
Usage: docxit [--version] [--help] <command> [<args>]\n\
Debug: <debug_command> [<args>]\n\
\n\
commands:\n\
    add         docxit add <file1> [<file2> ...]            add or remove files to index\n\
    commit      docxit commit -m \"<commit_message>\"         commit changes to docxit\n\
    diff        docxit diff <filename1> [<filename2> ...]   show difference between filename and its latest version\n\
    log         docxit log                                  show docxit commit log\n\
    listen      docxit listen                               get ready to receive\n\
    sendto      docxit sendto [-ip <ip> | <username>]       send current version to remote user\n\
    status      docxit status                               show index and workspace status\n\
    branch      docxit branch [-d] <branch_name>            create or delete branches\n\
    config      docxit config [options <args>]              set docxit configuration\n\
    help        docxit help                                 show this help\n\
    merge       docxit merge -m \"<message>\" <branch_name>   merge two branches\n\
    tag         docxit tag \"<tag_name>\" [<commit_value>]    tag specific commit\n\
    checkout    docxit checkout [-b] <new_branch_name>      move to another branch\n\
    deinit      docxit deinit                               delete docxit repository\n\
    init        docxit init                                 init docxit repository at current directory\n\
    reset       docxit reset [options]                      reset workspace to specific version\n\
    version     docxit version                              show docxit version info\n\
\n\
debug_commands:\n\
    printIndex          print the index file in a docxit repository\n\
\n\
\
";
#endif
    const char *version = "docxit version 1.0.0\n";

    if(argc <= 1){
        printf("%s", usage);
        exit(0);
	}

	char *cur = argv[1];
	switch(*cur ++){
        case 'a':
            if(!strcmp(cur, "dd")){
                checkDocxitPath(argv);

                if(argc < 3){
                    printf("nothing added\nmaybe you need 'docxit add .'?\n");
                    exit(0);
                }

                if(execv(EXE_DIR"add", argv) == -1){
                    perror(EXE_DIR"add");
                    exit(0);
                }
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                printf("the most similar command is %s\n", "add");
                exit(0);
            }

        case 'b':
            if(!strcmp(cur, "ranch")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"branch", argv) == -1){
                    perror(EXE_DIR"branch");
                    exit(0);
                }
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                printf("the most similar command is %s\n", "branch");
                exit(0);
            }

        case 'c':
            switch(*cur ++){
                case 'h':
                    if(!strcmp(cur, "eckout")){
                        checkDocxitPath(argv);
                        if(execv(EXE_DIR"checkout", argv) == -1){
                            perror(EXE_DIR"checkout");
                            exit(0);
                        }
                    }
                    else{
                        printf("unknown option: %s\n%s", argv[1], usage);
                        printf("the most similar command is %s\n", "checkout");
                        exit(0);
                    }

                case 'o':
                    switch(*cur ++){
                        case 'm':
                            if(!strcmp(cur, "mit")){
                                checkDocxitPath(argv);
                                if(execv(EXE_DIR"commit", argv) == -1){
                                    perror(EXE_DIR"commit");
                                    exit(0);
                                }
                            }
                            else{
                                printf("unknown option: %s\n%s", argv[1], usage);
                                printf("the most similar command is %s\n", "commit");
                                exit(0);
                            }
                        case 'n':
                           if(!strcmp(cur, "fig")){
                                if(system(EXE_DIR"updateDocxitPath.sh") == -1){
                                    printf("fatal: %s: cannot execute file\n", "updateDocxitPath.sh");
                                    exit(0);
                                }
                                docxitPath();
                                argv[1] = (char *)DOCXIT_PATH.c_str();
                                if(execv(EXE_DIR"config", argv) == -1){
                                    perror(EXE_DIR"config");
                                    exit(0);
                                }
                            }
                            else{
                                printf("unknown option: %s\n%s", argv[1], usage);
                                printf("the most similar command is %s\n", "config");
                                exit(0);
                            }
                        default:
                            printf("unknown option: %s\n%s", argv[1], usage);
                            printf("the most similar command is %s\n", "commit config");
                            exit(0);
                    }

                default:
                    printf("unknown option: %s\n%s", argv[1], usage);
                    exit(0);
            }

        case 'd':
            switch(*cur ++){
                case 'e':
                    if(!strcmp(cur, "init")){
                        checkDocxitPath(argv);
                        if(execv(EXE_DIR"deinit", argv) == -1){
                            perror(EXE_DIR"deinit");
                            exit(0);
                        }
                    }
                    else{
                        printf("unknown option: %s\n%s", argv[1], usage);
                        printf("the most similar command is %s\n", "deinit");
                        exit(0);
                    }

                case 'i':
                    if(!strcmp(cur, "ff")){
                        checkDocxitPath(argv);
                        if(execv(EXE_DIR"diff", argv) == -1){
                            perror(EXE_DIR"diff");
                            exit(0);
                        }
                    }
                    else{
                        printf("unknown option: %s\n%s", argv[1], usage);
                        printf("the most similar command is %s\n", "diff");
                        exit(0);
                    }

                default:
                    printf("unknown option: %s\n%s", argv[1], usage);
                    exit(0);
            }


        case 'h':
            if(!strcmp(cur, "elp")){
                printf("%s", usage);
                exit(0);
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                exit(0);
            }

        case 'i':
            if(!strcmp(cur, "nit")){
				if(system(EXE_DIR"updateDocxitPath.sh") == -1){
                    printf("fatal: %s: cannot execute file\n", "updateDocxitPath.sh");
                    exit(0);
                }
                if(docxitPath())
                    printf("Nested initialization not supported\n");
                else if(execv(EXE_DIR"init", argv) == -1)
                    perror(EXE_DIR"init");
                exit(0);
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                printf("the most similar command is %s\n", "init");
                exit(0);
            }

        case 'l':
            if(!strcmp(cur, "og")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"log", argv) == -1){
                    perror(EXE_DIR"log");
                    exit(0);
                }
            }
            else if(!strcmp(cur, "isten")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"listen", argv) == -1){
                    perror(EXE_DIR"listen");
                    exit(0);
                }
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                if(argv[1][1] == 'o')
                    printf("the most similar command is %s\n", "log");
                else if(argv[1][1] == 'i')
                    printf("the most similar command is %s\n", "listen");
                else
                    printf("the most similar command is %s\n", "log listen");
                exit(0);
            }

        case 'm':
            if(!strcmp(cur, "erge")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"merge", argv) == -1){
                    perror(EXE_DIR"merge");
                    exit(0);
                }
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                printf("the most similar command is %s\n", "merge");
                exit(0);
            }

        case 'r':
            if(!strcmp(cur, "eset")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"reset", argv) == -1){
                    perror(EXE_DIR"reset");
                    exit(0);
                }
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                printf("the most similar command is %s\n", "reset");
                exit(0);
            }

        case 's':
            if(!strcmp(cur, "tatus")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"status", argv) == -1){
                    perror(EXE_DIR"status");
                    exit(0);
                }
            }
            else if(!strcmp(cur, "endto")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"sendto", argv) == -1){
                    perror(EXE_DIR"sendto");
                    exit(0);
                }
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                if(argv[1][1] == 't')
                    printf("the most similar command is %s\n", "status");
                else if(argv[1][1] == 'e')
                    printf("the most similar command is %s\n", "sendto");
                else
                    printf("the most similar command is %s\n", "status sendto");
                exit(0);
            }

        case 't':
            if(!strcmp(cur, "ag")){
                checkDocxitPath(argv);
                if(execv(EXE_DIR"tag", argv) == -1){
                    perror(EXE_DIR"tag");
                    exit(0);
                }
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                printf("the most similar command is %s\n", "tag");
                exit(0);
            }

        case 'v':
            if(!strcmp(cur, "ersion")){
                printf("%s", version);
                exit(0);
            }
            else{
                printf("unknown option: %s\n%s", argv[1], usage);
                printf("the most similar command is %s\n", "version");
                exit(0);
            }

        case '-':
            if(*cur ++ == '-'){
                switch(*cur ++){
                    case 'h':
                        if(!strcmp(cur, "elp")){
                            printf("%s", usage);
                            exit(0);
                        }
                        else{
                            printf("unknown option: %s\n%s", argv[1], usage);
                            exit(0);
                        }

                    case 'v':
                        if(!strcmp(cur, "ersion")){
                            printf("%s", version);
                            exit(0);
                        }
                        else{
                            printf("unknown option: %s\n%s", argv[1], usage);
                            printf("the most similar command is %s\n", "--version");
                            exit(0);
                        }

                    default:
                        printf("unknown option: %s\n%s", argv[1], usage);
                        exit(0);
                }
            }
            else {
                printf("unknown option: %s\n%s", argv[1], usage);
                exit(0);
            }

        default:
            printf("unknown option: %s\n%s", argv[1], usage);
            exit(0);
	}
	return 0;
}
