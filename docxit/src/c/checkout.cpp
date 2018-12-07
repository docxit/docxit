#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include"shellCommand.h"
#include "commitTree.h"
#include "switchVersion.h"

static void printHelp(){
    printf("\
Usage: docxit checkout <branch_name>        switch to branch\n\
       docxit checkout -b <new_branch>      create and switch to a new branch\n");

    exit(0);
}

int main(int argc, char *argv[])
{
    if(argc <= 2) {
        printHelp();
    }

    // switch to a branch
    else if(argc == 3){
        if(*argv[2] == '-') printHelp();
        string path = argv[1];
        path = path + ".docxit/refs/heads/" + argv[2];
        string cbi = "if [ ! -f " + path + " ]; then echo \"error: branch '" + argv[2] + "' not found\"\nelse\n\techo -n '" + path + "'>" + argv[1] + ".docxit/HEAD\necho \"switch to branch '" + argv[2] + "'\"\nfi";
        if(system(cbi.c_str()) == -1){
            printf("fatal: switch to branch failed\n");
        }
        string key = shellCommand("[ -f " + path + " ]&&echo -n y");
        if(key == "y"){
            key = shellCommand("cat " + path);
            changeIndex(key.c_str(), argv[1]);
            switchVersion(argv[1]);
        }
    }

    // create and switch to a branch
    else if(argc == 4){
        /// here should check branch name without ' ' '/' and so on
        if(!strcmp(argv[2], "-b")){
            if(*argv[3] == '-') printHelp();

            // get current branch
            string curbr = "cat ";
            curbr = curbr + argv[1] + ".docxit/HEAD";
            curbr = shellCommand(curbr);

            string path = argv[1];
            path = path + ".docxit/refs/heads/" + argv[3];
            string cbi = "if [ -f " + path + " ]; then echo \"error: branch '" + argv[3] + "' exists\"\nelse\n\tcp " + curbr + " " + path + "\necho 'create and switch to new branch " + argv[3] + "'\necho -n '" + path + "'>" + argv[1] + ".docxit/HEAD\nfi";
            if(system(cbi.c_str()) == -1){
                printf("fatal: create and switch to new branch failed\n");
            }
        }
        else printHelp();
    }
    return 0;
}

