#include "mergeRecords.h"

void mergeRecords(string targetIndex, string sourceIndex, string targetBranchName, string sourceBranchName, string path){
    Records rect = openIndex(targetIndex.c_str());
    Records recs = openIndex(sourceIndex.c_str());
    int i;
    vector<string> con;
    for(i = 0; i < recs.length; i ++){
        if(recs.base[i].kind != unchanged){
            printf("please commit before merging\n");
            exit(0);
        }
        RecordPtr ptr = getPtrOfDocxitRecord(rect, recs.base[i].name);
        if(ptr == NULL) {
            recs.base[i].kind = add;
            insertDocxitRecord(&rect, recs.base[i]);
        }
        else{
            if(isRecordKey(ptr, recs.base[i].key)) continue;
            string save = recs.base[i].name;
            con.push_back(save);
            int pos = save.rfind('/');
            string tempstr1 = save.substr(0, pos + 1) + targetBranchName + "_" + save.substr(pos + 1);
            string tempstr2 = save.substr(0, pos + 1) + sourceBranchName + "_" + save.substr(pos + 1);

            setRecordName(ptr, tempstr1.c_str());
            setRecordName(&recs.base[i], tempstr2.c_str());
            recs.base[i].kind = add;
            insertDocxitRecord(&rect, recs.base[i]);
        }
    }
    writeRecordsToFile(targetIndex.c_str(), rect);

    freeRecords(&rect);
    freeRecords(&recs);

    switchVersion(path, "null");

    if(con.size() != 0) printf("\nconflict:\n");
    for (auto cf : con){
        printf("\t%s\n", cf.c_str());
    }
    for (auto cf : con){
        int pos = cf.rfind('/');
        string tempstr1 = cf.substr(0, pos + 1) + targetBranchName + "_" + cf.substr(pos + 1);
        string tempstr2 = cf.substr(0, pos + 1) + sourceBranchName + "_" + cf.substr(pos + 1);
        string cmd = "java -jar /usr/local/lib/docxit/fileop.jar merge " + tempstr1 + " " + tempstr2 + " " + cf + " " + targetBranchName + " " + sourceBranchName;
        if(system(cmd.c_str()) == -1){
            printf("fatal: java merge failed\n");
            exit(0);
        }
    }


}
