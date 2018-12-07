#include"commitTree.h"


void changeIndex(const char *commitkey, const char *path)
{
    string commitobjpath = "";
    string key = commitkey;
    commitobjpath = commitobjpath + path;
    commitobjpath = commitobjpath + ".docxit/object/";
    string objpath = commitobjpath;
    commitobjpath = commitobjpath + key.substr(0,2);
    commitobjpath = commitobjpath + "/" + key.substr(2,38);
    void *buff = (CommitStruct *)malloc(sizeof(CommitStruct));
    FILE *fh = fopen(commitobjpath.c_str(), "rb");
    fread(buff, sizeof(CommitStruct), 1, fh);
    key = ((CommitStruct *)buff)->key;
    free(buff);
    fclose(fh);
    string indexobjpath = objpath + key.substr(0,2) + "/" + key.substr(2,38);
    cout << "commitbojpath : " << commitobjpath << endl;
    string cmdcp = "cp " + indexobjpath + " " + path + ".docxit/index";
    cout << "cmdcp : " << cmdcp << endl;
    shellCommand(cmdcp);
}


CommitStruct *createCommitStruct(const char *key, const char *message)
{
    CommitStruct *cs = (CommitStruct *)malloc(sizeof(CommitStruct));
    //author is saved in file config
    time_t rawtime;
    struct tm *ptminfo;

    time(&rawtime);
    ptminfo = localtime(&rawtime);
    strcpy(cs->committime, asctime(ptminfo));
    //read time
    strcpy(cs->key, key);
    cs->parentnum = 0;
    cs->childnum = 0;
    strcpy(cs->author, getUserName(configpath()).c_str());
    strcpy(cs->commitmessage, message);
    return cs;
}
void writeCommitStructToFile(const CommitStruct *cf, const char *filename){
    FILE *fp = fopen(filename, "wb");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", filename);
        exit(0);
    }

    fwrite(cf, sizeof(CommitStruct), 1, fp);

    fclose(fp);
}

void freeCommitStruct(CommitStruct **cs){
    free(*cs);
    *cs = NULL;
}
void insertCommitObjectToTree(const char *key, const char *path)
{
//open file current branch(save in file HEAD), pass the key to parent_key, open parent_key file and write key into it, open key file and write parent_key into it,
//change the key in current branch into key

/// HEAD should contains full path of branch-file without '\n'.

    // get parent key
    string inst = "cat `cat ";
    inst = inst + path + ".docxit/HEAD`";
    string parentkey = shellCommand(inst);
    string curkey = key;

    // check if it is the first commit
    if(parentkey != "null") {

        // open parent commit object
        string dir = path;
        dir = dir + ".docxit/object/" + parentkey.substr(0,2) + '/' + parentkey.substr(2,38);
        FILE *fpp = fopen(dir.c_str(),"r+b");
        if(fpp == NULL){
            printf("fatal error: %s: cannot open file\n", dir.c_str());
            exit(0);
        }

        // open current commit object
        dir = path;
        dir = dir + ".docxit/object/" + curkey.substr(0,2) + '/' + curkey.substr(2,38);
        FILE *fpc = fopen(dir.c_str(),"r+b");
        if(fpc == NULL){
            printf("fatal error: %s: cannot open file\n", dir.c_str());
            exit(0);
        }

        // read parent commit struct
        CommitStruct *pbuf = (CommitStruct *)malloc(sizeof(CommitStruct));
        if(fread(pbuf, sizeof(CommitStruct), 1, fpp) == 0){
            printf("fatal: %s%s: read file error\n", "commit object ", parentkey.c_str());
            exit(0);
        }

        // read current commit struct
        CommitStruct *cbuf = (CommitStruct *)malloc(sizeof(CommitStruct));
        if(fread(cbuf, sizeof(CommitStruct), 1, fpc) == 0){
            printf("fatal: %s%s: read file error\n", "commit object ", curkey.c_str());
            exit(0);
        }

        // write curkey into parent struct
        if(pbuf->childnum == 10){
            printf("fatal: too many branches for current commit node\n");
            exit(0);
        }
        strcpy(pbuf->childkey[(int)(pbuf->childnum ++)], key);

        // write parent key into current struct
        if(cbuf->parentnum == 2){
            printf("fatal: there are already two parents for current commit node\n");
            exit(0);
        }
        strcpy(cbuf->parentkey[(int)(cbuf->parentnum ++)], parentkey.c_str());

        // rewind file pointer
        rewind(fpp);
        rewind(fpc);

        // write struct to file
        fwrite(pbuf, sizeof(CommitStruct), 1, fpp);
        fwrite(cbuf, sizeof(CommitStruct), 1, fpc);

        // free buf
        free(pbuf);
        free(cbuf);

        // close files
        fclose(fpp);
        fclose(fpc);
    }

    // change branch file
    string instw = "echo -n '" + curkey + "'>`cat " + path + ".docxit/HEAD`";
    if(system(instw.c_str()) == -1){
        printf("fatal: %s: cannot execute\n", instw.c_str());
        exit(0);
    }
}

void printCommitObject(const char *key, const char *path)
{
    string keyvalue = key;
    string dir = path;
    dir = dir + ".docxit/object/" + keyvalue.substr(0,2) + '/' + keyvalue.substr(2,38);
    FILE *fp = fopen(dir.c_str(),"rb");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", dir.c_str());
        exit(0);
    }
    CommitStruct *buf = (CommitStruct *)malloc(sizeof(CommitStruct));
    if(fread(buf, sizeof(CommitStruct), 1, fp) == 0){
        printf("fatal: %s%s: read file error\n", "commit object ", key);
        exit(0);
    }

    printf("Author: %s\nData:   %s\n        %s\n\n",buf->author,buf->committime,buf->commitmessage);
    free(buf);
    fclose(fp);
}


static std::vector<std::string> split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> spiltCollection;
    if(str.size()==0)
        return spiltCollection;
    int start = 0;
    int idx = str.find(delim, start);
    while( idx != (int)std::string::npos )
    {
        spiltCollection.push_back(str.substr(start, idx-start));
        start = idx+delim.size();
        idx = str.find(delim, start);
    }
    spiltCollection.push_back(str.substr(start));
    return spiltCollection;
}


void printCommitTree(const char *key, const char *path, const char *currentBranch){
/// todo: print head->master

    printf("commit  %s  ", key);

    // print branch
    string grepstr = "cd ";
    grepstr = grepstr + path + ".docxit/refs/heads/ ;[ -n \"`ls`\" ]&&grep '" + key + "' *";
    grepstr = shellCommand(grepstr);
    auto alls = split(grepstr, "\n");
    for (const auto &allbr: alls) {
        int len = allbr.find(':');
        if(len == -1) continue;
        string s = allbr.substr(0, len);
        if(s != currentBranch)printf(" (%s) ", s.c_str());
        else printf(" (HEAD -> %s) ", s.c_str());
    }

    // print tag
    grepstr = "cd ";
    grepstr = grepstr + path + ".docxit/refs/tags/ ;[ -n \"`ls`\" ]&&grep '" + key + "' *";
    grepstr = shellCommand(grepstr);
    auto allt = split(grepstr, "\n");
    for (const auto &allbr: allt) {
        int len = allbr.find(':');
        if(len == -1) continue;
        printf(" (tag: %s) ", allbr.substr(0, len).c_str());
    }

    printf("\n");

    string keyvalue = key;
    string dir = path;
    dir = dir + ".docxit/object/" + keyvalue.substr(0,2) + '/' + keyvalue.substr(2,38);
    FILE *fp = fopen(dir.c_str(),"rb");
    if(fp == NULL){
        printf("fatal error: %s: cannot open file\n", dir.c_str());
        exit(0);
    }
    CommitStruct *buf = (CommitStruct *)malloc(sizeof(CommitStruct));
    if(fread(buf, sizeof(CommitStruct), 1, fp) == 0){
        printf("fatal: %s%s: read file error\n", "commit object ", key);
        exit(0);
    }

    printf("Author: %s\nData:   %s\n        %s\n\n",buf->author,buf->committime,buf->commitmessage);

    // copy parent attribute
    int pn = buf->parentnum;
    char pkey[2][41];
    memcpy(pkey, buf->parentkey, sizeof(pkey));

    // free memory
    free(buf);
    fclose(fp);

    while(pn) printCommitTree(pkey[-- pn], path, currentBranch);
}
