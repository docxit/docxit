#include "indexOp.h"
#include "shellCommand.h"

#define USAGE "\
Usage: docxit diff <filename1> [<filename2> ...]        show difference between filename and its latest version\n\
"

int main(int argc, char *argv[]){
//
    string cwd = shellCommand("echo -n $PWD/");
    string dpath = argv[1];
    string indexparh = dpath + ".docxit/index";

    if(argc == 2 || *argv[2] == '-'){
        printf("%s", USAGE);
        exit(0);
    }

    Records rec = openIndex(indexparh.c_str());

    for(int i = 2; i < argc; i ++){
        string curfile = cwd + argv[i];
        RecordPtr ptr = getPtrOfDocxitRecord(rec, curfile.c_str());
        if(ptr == NULL){
            printf("error: %s: cannot find file in index\n", curfile.c_str());
            exit(0);
        }
        string key = getRecordKey(ptr);
        key = "java -jar /usr/local/lib/docxit/fileop.jar diff " + curfile + " " + dpath + ".docxit/object/" + key.substr(0,2) +  '/' + key.substr(2,38);
        if(system(key.c_str()) == -1){
            printf("fatal: execute fileop.jar failed\n");
            exit(0);
        }
    }

    freeRecords(&rec);
}
