#include"mergeOp.h"

string getHeadBranch(const char *docxitpath)
{
    string headpath = docxitpath;
    headpath += ".docxit/HEAD";
    string cmd = "cat " + headpath;
    string branchpath = shellCommand(cmd);
    string dirpath = docxitpath;
    dirpath += ".docxit/refs/heads/";
    string branchname = branchpath.substr(dirpath.length(),branchpath.length()-dirpath.length());
    return branchname;
}

int isBranch(const char *branchname, const char *docxitpath)
{
    int flag = 0;
    string branchpath = docxitpath;
    branchpath = branchpath + ".docxit/refs/heads/";
    branchpath = branchpath + branchname;
    string cmd = "[ -f " + branchpath + " ] && echo true || false";
    string res = shellCommand(cmd);
    if(*res.c_str() == 't')
        flag = 1;
    return flag;
}

CommitStruct *csCommitkey(const char *commitkey, const char *docxitpath)
{
    CommitStruct *cs = (CommitStruct *)malloc(sizeof(CommitStruct));
    ifstream fh;
    string key = commitkey;
    string cbpath = docxitpath;
    cbpath = cbpath + ".docxit/object/";
    cbpath = cbpath + key.substr(0,2) + "/" + key.substr(2,38);
    fh.open(cbpath.c_str(),ios::binary);
    fh.read(cs,sizeof(CommitStruct));
    fh.close();
    return cs;
}

int branchSearch(CommitStruct *p, CommitStruct *c, const char *docxitpath)
{
    CommitStruct *t;
    int first = 1;
    if(strcmp(p->key,c->key) == 0)
        return 1;
    while(c->parentnum > 0)
    {
        if(strcmp(p->key,c->key) == 0)
            return 1;
        if(first == 1)
        {
            first = 0;
            continue;
        }
        t = c;
        c = csCommitkey(c->parentkey[0],docxitpath);
        free(t);
    }
    return 0;
}

string branchKey(const char *branchname, const char *docxitpath)
{
    string branchpath = docxitpath;
    branchpath = branchpath + "refs/heads/";
    branchpath = branchpath + branchname;
    string key,cmd;
    cmd = "cat " + branchpath;
    key = shellCommand(cmd);
    return key;
}
//0=no;1=pbranch is parent node;2=cbranch is parent node
int isInSameBranch(const char *pbranch, const char *cbranch, const char *docxitpath)
{
    int flag = 0;
    CommitStruct *p,*q;
    string key;
    key = branchKey(pbranch, docxitpath);
    p = csCommitkey(key.c_str(), docxitpath);
    key = branchKey(cbranch, docxitpath);
    q = csCommitkey(key.c_str(), docxitpath);
    if(branchSearch(p,q) == 1)
        flag = 1;
    else if(branchSearch(q,p) == 1)
        flag = 2;
    else
        flag = 0;
    free(p);
    free(q);
    return flag;
}

void changBranchKey(const char *tobranchname, const char *frombranchname, const char *docxitpath)
{
    string branchpath = docxitpath;
    branchpath = branchpath + "refs/heads/";
    branchpath = branchpath + tobranchname;
    ofstream fh(branchpath.c_str());
    string key = branchKey(frombranchname, docxitpath);
    fh << key;
    fh.close();
}
