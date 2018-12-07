#include "switchVersion.h"

void switchVersion(string path){
    string indexpath = path + ".docxit/index";
    Records rec = openIndex(indexpath.c_str());
    for(int i = 0; i < rec.length; i ++){
        string key = rec.base[i].key;
        key = "cp " + path + ".docxit/object/" + key.substr(0,2) + '/' + key.substr(2,38) + " " + rec.base[i].name;
        if(system(("rm -rf `ls " + path + " -A | grep -v .docxit`").c_str()) == -1){
            printf("fatal: rm: cannot execute\n");
            exit(0);
        }
        if(system(key.c_str()) == -1){
            printf("fatal: %s: cannot execute\n", key.c_str());
            exit(0);
        }
    }
    freeRecords(&rec);
}
