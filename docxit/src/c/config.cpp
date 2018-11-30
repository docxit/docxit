#include <iostream>
#include <string.h>
#include<string>
#include"configOp.h"

using namespace std;

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("\
Usage: docxit config --list\n\
                     --myname <user_name>\n\
                     --adduser <remote_user_name> <ip>\n\
                     --removeuser <remote_user_name>\n");
        exit(0);
    }

    const char *conpath = configpath();

    if(strcmp(argv[2], "--list") == 0){
        printConfig(conpath);
        exit(0);
    }

    else if(argc < 4){
        printf("\
Usage: docxit config --list\n\
                     --myname <user_name>\n\
                     --adduser <remote_user_name> <ip>\n\
                     --removeuser <remote_user_name>\n");
        exit(0);
    }

    if(strcmp(argv[2], "--myname") == 0)
    {
        changeUserName(argv[3], conpath);
        exit(0);
    }
    else if(strcmp(argv[2], "--adduser") == 0)
    {
        if(argc < 5)
        {
            printf("Usage: docxit config --adduser <remote_user_name> <ip>\n");
            exit(0);
        }
        addRemote(argv[3], argv[4], conpath);
        exit(0);
    }
    else if(strcmp(argv[2], "--removeuser") == 0)
    {
        removeRemoteByUserName(argv[3], conpath);
        exit(0);
    }
    else
    {
        printf("\
Usage: docxit config --list\n\
                     --myname <user_name>\n\
                     --adduser <remote_user_name> <ip>\n\
                     --removeuser <remote_user_name>\n");
        exit(0);
    }

}
