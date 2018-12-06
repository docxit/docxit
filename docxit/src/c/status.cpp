#include "indexOp.h"
#include "getBranch.h"
#include "sha1.h"
#include <vector>

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

int findAllFilesNotExist(Records rec){
    int i, ret = 0;
    for(i = 0; i < rec.length; i ++){
        const char *name = getRecordName(&rec.base[i]);
        char ins[4096];
        sprintf(ins, "[ ! -f %s ] && echo -n y", name);
        string isRm = shellCommand(ins);
        if(isRm == "y" && rec.base[i].kind != removed){
            if(ret == 0) printf("Unstaged changes:\n");
            ret = 1;
            printf("\tremove: %s\n", name);
        }
        else {
            string sha = valueSHA_1(name);
            if((rec.base[i].kind == changed && rec.base[i].newkey != sha) ||
               (rec.base[i].kind == add && rec.base[i].key != sha) ||
               (rec.base[i].kind == unchanged && rec.base[i].key != sha)){
                if(ret == 0) printf("Unstaged changes:\n");
                ret = 1;
                printf("\tchange: %s\n", name);
            }
        }
    }
    return ret;
}

int main(int argc, char *argv[]){
    char indexpath[4096] = {'\0'};
    strcat(indexpath, argv[1]);
    strcat(indexpath, ".docxit/index");
    Records rec = openIndex(indexpath);

    printCurrentBranch(argv[1]);
    printf("\n");
    int clean = !printStatus(rec);
    if(!clean) printf("\n");
    int first = 1;

    string cmd = "find ";
    cmd = cmd + argv[1] + " -type f | grep -v \".docxit\"";
    cmd = shellCommand(cmd);
    auto allfile = split(cmd, "\n");

    // find all files in index but not exist
    int fret = findAllFilesNotExist(rec);
    if(fret) printf("\nUse docxit add <file_name> to stage changes\n\n");

    // find all files that exist but not in index
    for (const auto &s: allfile) {
        if(s == "") continue;
        RecordPtr ptr = getPtrOfDocxitRecord(rec, s.c_str());
        if(ptr == NULL || isRecordKind(ptr, removed)){
            if(first){
                first = 0;
                printf("Untracked files:\n");
            }
            printf("\t%s\n", s.c_str());
        }
    }
    if(!first) printf("\n");
    if(first == 0){
        if(clean){
            printf("提交为空，但是存在尚未跟踪的文件\n");
        }
        else{
            printf("有要提交的文件，使用 docxit commit -m <info> 提交\n");
        }
    }
    else{
        if(clean == 0){
            printf("有要提交的文件，使用 docxit commit -m <info> 提交\n");
        }
        else{
            if(fret == 0)printf("clean workspace, nothing to commit!\n");
        }
    }
    freeRecords(&rec);
}
