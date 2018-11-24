#ifndef __BLOB_CREATE_H__
#define __BLOB_CREATE_H__

#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

void blobCreate(string filename, string value_sha1, const char* docxitrootpath);
// filename should be full path
void blobCreateMv(string filename, string value_sha1, const char* docxitrootpath);

#endif//__BLOB_CREATE_H__
