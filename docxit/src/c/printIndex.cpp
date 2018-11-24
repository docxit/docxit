#include "indexOp.h"
#include "docxitPath.h"

int main()
{
    int isrepo = docxitPath();
	if(isrepo == 0 || isrepo == 2){
        printf("fatal: not a docxit repository\n");
        exit(0);
    }
    string indexpath = DOCXIT_PATH + ".docxit/" + INDEX_FILE_NAME;
    Records rec = openIndex(indexpath.c_str());
    printRecords(rec);
    freeRecords(&rec);
    return 0;
}
