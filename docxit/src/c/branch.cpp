#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include"shellCommand.h"

static void printHelp(){
    printf("\
Usage: docxit branch                        show all branches\n\
       docxit branch <new_branch>           create a new branch\n\
       docxit branch -d <br1> [<br2> ...]   delete branches\n");

    exit(0);
}

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

int main(int argc, char *argv[])
{
    // show all branch
    if(argc <= 2) {

        // find current branch
        string curbr = "cat ";
        curbr = curbr + argv[1] + ".docxit/HEAD";
        curbr = shellCommand(curbr);
        curbr = curbr.substr(curbr.rfind('/') + 1);

        // get all branch
        string allbranch = "ls ";
        allbranch = allbranch + argv[1] + ".docxit/refs/heads/";
        allbranch = shellCommand(allbranch);

        // print all branch
        auto allbr = split(allbranch, "\n");
        for (const auto &s: allbr) {
            // cur br print *
            if(s == curbr){
                printf("* ");
            }
            else if(s == ""){
                continue;
            }
            else printf("  ");

            printf("%s\n", s.c_str());
        }
    }

    // new branch
    else if(argc == 3){
    /// here should check branch name without ' ' '/' and so on
        if(*argv[2] == '-') printHelp();

        // get current branch
        string curbr = "cat ";
        curbr = curbr + argv[1] + ".docxit/HEAD";
        curbr = shellCommand(curbr);

        // create new branch
        string path = argv[1];
        path = path + ".docxit/refs/heads/" + argv[2];
        string cbi = "if [ -f " + path + " ]; then echo \"error: branch '" + argv[2] + "' exists\"\nelse\n\tcp " + curbr + " " + path + "\necho 'create new branch " + argv[2] + "'\nfi";
        if(system(cbi.c_str()) == -1){
            printf("fatal: create new branch failed\n");
        }
    }

    // delete branch
    else if(argc > 3){
        if(!strcmp(argv[2], "-d")){
            for(int i = 3; i < argc; i ++){
                // get current branch
                string curbr = "cat ";
                curbr = curbr + argv[1] + ".docxit/HEAD";
                curbr = shellCommand(curbr);
                curbr = curbr.substr(curbr.rfind('/') + 1);

                // delete cur branch ?
                if(curbr == argv[i]){
                    printf("error: cannot delete current working branch '%s'\n", argv[i]);
                    exit(0);
                }

                /// here is not safe, for example, one can delete '../..' or 'a; rm -rf /'
                // delete
                string path = argv[1];
                path = path + ".docxit/refs/heads/" + argv[i];
                string cbi = "if [ ! -f " + path + " ]; then echo \"error: branch '" + argv[i] + "' not found\"\nelse\n\trm -f " + path + "\necho 'delete branch " + argv[i] + "'\nfi";
                if(system(cbi.c_str()) == -1){
                    printf("fatal: delete branch failed\n");
                }
            }
        }
        else printHelp();
    }
    return 0;
}

