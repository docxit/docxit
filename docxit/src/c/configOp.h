#ifndef __CONFIGOP_H__
#define __CONFIGOP_H__
#include<iostream>
#include<iomanip>
#include<istream>
#include<ostream>
#include<fstream>
#include<string.h>
#include<string>
#include"shellCommand.h"

#define MAX_CONFIG_PATH_LENGTH 50
#define MAX_ROMOTE_NUM 10
#define MAX_USERNAME_LENGTH 128
#define MAX_REMOTENAME_LENGTH 128
#define MAX_IP_LENGTH 32
#define CONFIGFILENAME ".docxitconfig"

using namespace std;

typedef struct
{
    char remotename[MAX_REMOTENAME_LENGTH];
    char remoteip[MAX_IP_LENGTH];
}RemoteStruct;

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    RemoteStruct remoteinfo[MAX_ROMOTE_NUM];
    int remotenum = 0;
}ConfigStruct;

const char *configpath();

void changeUserName(const char *username, const char *configpath);

string getUserName(const char *configpath);

void addRemote(const char *remotename, const char *ip, const char *configpath);

string getIPbyUserName(const char *username, const char *configpath);//if can't find return string with "error"

void removeRemoteByUserName(const char *username, const char *configpath);

void clearConfig(const char * configpath);

void printConfig(const char *configpath);

//~/.docxitconfig

#endif // __CONFIG_H__




