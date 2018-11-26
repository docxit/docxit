#ifndef __CONFIGOP_H__
#define __CONFIGOP_H__
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include<string.h>
#include<string>

#define MAX_ROMOTE_NUM 10
#define MAX_USERNAME_LENGTH 128
#define MAX_REMOTENAME_LENGTH 128
#define MAX_IP_LENGTH 32

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

void changeUserName(const char *username, const char *configpath);

string getUserName(const char *configpath);

void addRemote(const char *remotename, const char *ip, const char *configpath);

string getIPbyUserName(const char *username, const char *configpath);//if can't find return string with "error"

void removeRemoteByUserName(const char *username, const char *configpath);

void clearConfig(const char * configpath);

#ifdef DEBUG

void printConfig(const char *configpath);

#endif // DEBUG
//~/.docxitconfig

#endif // __CONFIG_H__




