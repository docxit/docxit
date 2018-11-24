#include "indexOp.h"
#include <assert.h>

 int main(){

    Records rec = openIndex("index");
    #ifdef DEBUG
    printRecords(rec);
    #endif // DEBUG
    assert(getPtrOfDocxitRecord(rec, "abc") == NULL);  //cannot find

    insertDocxitRecord(&rec, (DocxitRecord){unchanged, "abc", "40404", ""});
    insertDocxitRecord(&rec, (DocxitRecord){changed, "ddd", "404304", "3232"});
    insertDocxitRecord(&rec, (DocxitRecord){removed, "fff", "12222", "0000"});

    RecordPtr pos = getPtrOfDocxitRecord(rec, "fff");
    assert(isRecordKind(pos, removed) == 1);
    assert(isRecordNewkey(pos, "0000") == 1);

    pos = getPtrOfDocxitRecord(rec, "abc");
    setRecordKey(pos, "111");
    setRecordKind(pos, add);
    assert(getRecordKind(pos) == add);
    assert(isRecordKey(pos, "111") == 1);
    assert(isRecordNewkey(pos, "111") == 0);

    deleteDocxitRecordByPtr(pos);
    assert(getPtrOfDocxitRecord(rec, "abc") == NULL);  //cannot find

    writeRecordsToFile("index", rec);
    freeRecords(&rec);
 }
