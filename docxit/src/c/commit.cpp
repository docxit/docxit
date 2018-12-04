#include<iostream>
#include<fstream>
#include<string.h>
#include"sha1.h"
#include"blobCreate.h"
#include"indexOp.h"
#include"commitTree.h"

using namespace std;

int main(int argc, char *argv[])
{
    //cout <<  "arg1: " << argv[1] << endl << "arg2: " << argv[2] << endl << "arg3: " << argv[3] << endl;


    if(argc < 4 || strcmp(argv[2],"-m") != 0)
    {
        cout << "Usage: docxit commit -m \"<commit_message>\"" << endl;
        exit(0);
    }
    ifstream ifh;
    string docxitroot = argv[1];
    string head = docxitroot + ".docxit/HEAD";
    ifh.open(head.c_str());
    char ptrname[128];
    ifh.getline(ptrname,128);
    string ptr = ptrname;
    cout << "current branch is " << ptr.substr(ptr.rfind('/') + 1) << endl;
    string indexpath = docxitroot + ".docxit/" + INDEX_FILE_NAME;
    int change = commitIndex(indexpath.c_str());
    if(change == 0)
    {
        cout << "clean workspace, nothing to commit!" << endl;
    }
    else
    {
        string sha1Index = valueSHA_1(indexpath);
        string indexname = ".docxit/";
        indexname = indexname + INDEX_FILE_NAME;
        blobCreate(indexname, sha1Index, docxitroot.c_str());
        CommitStruct *cf = createCommitStruct(sha1Index.c_str(), argv[3]);
        writeCommitStructToFile(cf, ".docxit_commit_tempfile");
        string fn = ".docxit_commit_tempfile";
        string sha1tf = valueSHA_1(fn);//commit object's key
        blobCreateMv(fn, sha1tf, argv[1]);
        insertCommitObjectToTree(sha1tf.c_str(), argv[1]);
        printCommitObject(sha1tf.c_str(), argv[1]);
    }
}
