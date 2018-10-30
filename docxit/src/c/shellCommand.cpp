#include"shellCommand.h"

string shellCommand(string command)//read at most 128 bytes
{
    FILE *fpr;
    char buffer[128];
    fpr = popen(command.c_str(), "r");
    fread(buffer, 1, sizeof(buffer), fpr);
    pclose(fpr);
    string res = buffer;
    return res;
}

