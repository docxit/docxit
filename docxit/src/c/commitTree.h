




//branch master is created while docxit init is executed
//root is created while docxit init is executed, inited with null

CommitStruct *createCommitStruct(const char *key, const char *message);
//create a file that records commit key, author, commit time and commit message
//create the file's blob obj and return it's key value

void writeCommitStructToFile(CommitFile *cf, const char *filename);

void freeCommitStruct(CommitStruct **cs);

void insertCommitObjectToTree(const char *key);
//open file current branch(save in file HEAD), pass the key to parent_key, open parent_key file and write key into it, open key file and write parent_key into it,
//change the key in current branch into key
//if root is null, change root into key, change the branch in HEAD into key

void printTree();
//open root dfs, post order travel, print tree


typedef struct
{
    char key[41];
    char author[64];
    char committime[64];
    char commitmessage[256];
    char parentkey[2][41];
    char childkey[10][41];
    char parentnum;
    char childnum;
}CommitStruct;


