#include"shellCommand.h"

string shellCommand(string command)//read at most 128 bytes
{
    FILE *fpr;
    char buffer[256];
    fpr = popen(command.c_str(), "r");
    if(!fpr){
        perror(command.c_str());
        exit(0);
    }
    int num = fread(buffer, 1, sizeof(buffer), fpr);
    if(num == 0){
        return "";
    }
    else if(num >= 255){
        printf("fatal: instruction too long\n");
        exit(0);
    }
    pclose(fpr);
    buffer[num] = '\0';
    string res = buffer;
    return res;
}

