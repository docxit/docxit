#include"shellCommand.h"
#include"configOp.h"

int main()
{
    string com = "echo ~/config";
    char configpath[20];
    const char *configp = shellCommand(com).c_str();
    changeUserName("bty",configp);
    printConfig(configp);
    return 0;
}
