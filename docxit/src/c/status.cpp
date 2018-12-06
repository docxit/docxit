#include "indexOp.h"
#include "getBranch.h"
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

    for (const auto &s: allfile) {
        if(s == "") continue;
        if(getPtrOfDocxitRecord(rec, s.c_str()) == NULL){
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
            printf("clean workspace, nothing to commit!\n");
        }
    }
    freeRecords(&rec);
}
