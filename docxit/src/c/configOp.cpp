#include"configOp.h"

void changeUserName(const char *username, const char *configpath)
{
    ifstream ifh(configpath,ios::binary);
    if(!ifh.is_open())
    {
        cout << "open file config failed!" << endl;
        exit(0);
    }
    ConfigStruct *cs = (ConfigStruct *)malloc(sizeof(ConfigStruct));
    ifh.read((char *)cs, sizeof(ConfigStruct));
    ifh.close();
    strcpy(cs->username, username);
    ofstream ofh(configpath,ios::binary);
    ofh.write((char *)cs, sizeof(ConfigStruct));
    ofh.close();
    free(cs);
}

void addRemote(const char *remotename, const char *ip, const char *configpath)
{
    ifstream ifh(configpath,ios::binary);
    if(!ifh.is_open())
    {
        cout << "open file config failed!" << endl;
        exit(0);
    }
    ConfigStruct *cs = (ConfigStruct *)malloc(sizeof(ConfigStruct));
    ifh.read((char *)cs, sizeof(ConfigStruct));
    ifh.close();
    if(cs->remotenum == MAX_ROMOTE_NUM)
    {
        cout << "the remote num has reached the limited!" << endl;
        exit(0);
    }
    for(int i = 0; i < cs->remotenum; i++)
    {
        if(strcmp(cs->remoteinfo[i].remotename, remotename) == 0)
        {
            cout << "remote member " << remotename << " is already in the remote list!" << endl;
            return;
        }
    }
    strcpy(cs->remoteinfo[cs->remotenum].remotename, remotename);
    strcpy(cs->remoteinfo[cs->remotenum].remoteip, ip);
    cs->remotenum ++;
    ofstream ofh(configpath,ios::binary);
    ofh.write((char *)cs, sizeof(ConfigStruct));
    ofh.close();
    free(cs);
}

string getIPbyUserName(const char *username, const char *configpath)
{
    ifstream ifh(configpath,ios::binary);
    if(!ifh.is_open())
    {
        cout << "open file config failed!" << endl;
        exit(0);
    }
    ConfigStruct *cs = (ConfigStruct *)malloc(sizeof(ConfigStruct));
    ifh.read((char *)cs, sizeof(ConfigStruct));
    ifh.close();
    for(int i = 0; i < cs->remotenum; i++)
    {
        if(strcmp(cs->remoteinfo[i].remotename, username) == 0)
        {
            string remoteip = cs->remoteinfo[i].remoteip;
            free(cs);
            return remoteip;
        }
    }
    free(cs);
    string remotip = "can_not_find";
    return remotip;
}

string getUserName(const char *configpath)
{
    ifstream ifh(configpath,ios::binary);
    if(!ifh.is_open())
    {
        cout << "open file config failed!" << endl;
        exit(0);
    }
    ConfigStruct *cs = (ConfigStruct *)malloc(sizeof(ConfigStruct));
    ifh.read((char *)cs, sizeof(ConfigStruct));
    ifh.close();
    char un[MAX_USERNAME_LENGTH];
    strcpy(un, cs->username);
    string username = un;
    free(cs);
    return username;
}

void removeRemoteByUserName(const char *username, const char *configpath)
{
    ifstream ifh(configpath,ios::binary);
    if(!ifh.is_open())
    {
        cout << "open file config failed!" << endl;
        exit(0);
    }
    ConfigStruct *cs = (ConfigStruct *)malloc(sizeof(ConfigStruct));
    ifh.read((char *)cs, sizeof(ConfigStruct));
    ifh.close();
    for(int i = 0; i < cs->remotenum; i++)
    {
        if(strcmp(cs->remoteinfo[i].remotename, username) == 0)
        {
            for(int j = i; j < cs->remotenum-1; j++)
            {
                cs->remoteinfo[j] = cs->remoteinfo[j+1];
            }
            cs->remotenum --;
            ofstream ofh(configpath,ios::binary);
            ofh.write((char *)cs, sizeof(ConfigStruct));
            ofh.close();
            cout << "remote user " << username << " is removed from list" << endl;
            free(cs);
            return;
        }
    }
    free(cs);
    cout << "remote user" << username << " does not exit in the remote list" << endl;
}

void clearConfig(const char * configpath)
{
    ConfigStruct *cs = (ConfigStruct *)malloc(sizeof(ConfigStruct));
    strcpy(cs->username, "null");
    cs->remotenum = 0;
    ofstream ofh(configpath,ios::binary);
    ofh.write((char *)cs, sizeof(ConfigStruct));
    ofh.close();
    free(cs);
    cout << "file config is cleared!" << endl;
}

#ifdef DEBUG

void printConfig(const char *configpath)
{
    ifstream ifh(configpath,ios::binary);
    if(!ifh.is_open())
    {
        cout << "open file config failed!" << endl;
        exit(0);
    }
    ConfigStruct *cs = (ConfigStruct *)malloc(sizeof(ConfigStruct));
    ifh.read((char *)cs, sizeof(ConfigStruct));
    ifh.close();
    int rn = cs->remotenum;
    cout << cs->username << endl;
    cout << rn << endl;
    for(int i = 0; i < rn; i++)
    {
        cout << cs->remoteinfo[i].remotename << "    " << cs->remoteinfo[i].remoteip << endl;
    }
    free(cs);
}

#endif // DEBUG

