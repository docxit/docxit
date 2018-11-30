#include <iostream>
#include <string.h>
#include<string>
#include"configOp.h"
#include"shellCommand.h"

using namespace std;

const char *configpath()
{
    string command = "echo ~/";
    string root = shellCommand(command);
    root = root.substr(0,root.length()-1);
    static char conpath[MAX_CONFIG_PATH_LENGTH];
    strcpy(conpath, root.c_str());
    strcat(conpath, CONFIGFILENAME);
    return conpath;
}

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("\
Usage: docxit config --myname <user_name>\n\
                     --adduser <remote_user_name> <ip>\n\
                     --removeuser <remote_user_name>\n");
        exit(0);
    }
    const char *conpath = configpath();
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
Usage: docxit config --myname <user_name>\n\
                     --adduser <remote_user_name> <ip>\n\
                     --removeuser <remote_user_name>\n");
        exit(0);
    }

}
