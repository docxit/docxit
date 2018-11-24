#include"indexOp.h"



int main()
{
#ifdef DEBUG
    Records rec = openIndex(INDEX_FILE_NAME);
    printRecords(rec);
    freeRecords(&rec);
#endif // DEBUG
    return 0;
}
