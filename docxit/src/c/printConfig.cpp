#include"shellCommand.h"
#include"configOp.h"

int main()
{
    string com = "echo ~/config";
    string configp = shellCommand(com);
    configp = configp.substr(0,configp.length()-1);
    cout << configp << endl;
    printConfig(configp.c_str());


    return 0;
}
