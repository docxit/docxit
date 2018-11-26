#include"shellCommand.h"
#include"configOp.h"

int main()
{
    string com = "echo ~/config";
    string configp = shellCommand(com);
    configp = configp.substr(0,configp.length()-1);
    cout << configp << endl;
    changeUserName("bty",configp.c_str());
    changeUserName("btybty",configp.c_str());
    cout << getIPbyUserName("yxy",configp.c_str()) << endl;
    cout << getIPbyUserName("yxyr",configp.c_str()) << endl;
    clearConfig(configp.c_str());
    printConfig(configp.c_str());
    for(int i =0; i < 3; i++)
    {
        addRemote("yxy","128.325.25.36.32",configp.c_str());
        addRemote("zjb","125.369.32.28.14",configp.c_str());
        addRemote("cz","125.369.32.28.14",configp.c_str());
    }
    removeRemoteByUserName("zjb",configp.c_str());
    return 0;
}
