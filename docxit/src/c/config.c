#include <stdio.h>
#include <string.h>
#include"shellCommand.h"
#include"configOp.h"

const char *configpath()
{

}


int main(int argc, char *argv[]){
    if(argc < 4){
        printf("\
Usage: docxit config --myname <user_name>\n\
                     --adduser <remote_user_name> <ip>\n\
                     --removeuser <remote_user_name>\n");
        exit(0);
    }
    if(strcmp(argv[2], "--myname") == 0)
    {

    }

}
