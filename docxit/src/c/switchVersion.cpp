#include "switchVersion.h"

void switchVersion(string path, string newkey){
    string indexpath = path + ".docxit/index";
    Records rec = openIndex(indexpath.c_str());
    string ins = "cd " + path + ";rm -rf `ls -A | grep -v .docxit`;";
//    printf("---%s\n", ins.c_str());
//    if(system(ins.c_str()) == -1){
//        printf("fatal: rm: cannot execute\n");
//        exit(0);
//    }printf("2\n");
    for(int i = 0; i < rec.length; i ++){
        string key = rec.base[i].key;
        string name = rec.base[i].name;
        string dir = name.substr(0, name.rfind("/"));
        key = "cp " + path + ".docxit/object/" + key.substr(0,2) + '/' + key.substr(2,38) + " " + rec.base[i].name;
        key = "mkdir -p " + dir + "&&"+ key + ";";
        ins += key;
//        if(system(key.c_str()) == -1){
//            printf("fatal: %s: cannot execute\n", key.c_str());
//            exit(0);
//        }
    }
    if(newkey != "null")ins += "echo -n " + newkey + ">`cat " + path + ".docxit/HEAD`";
    if(system(ins.c_str()) == -1){
        printf("fatal: %s: cannot execute\n", ins.c_str());
        exit(0);
    }
    freeRecords(&rec);
}
