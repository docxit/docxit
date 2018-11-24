#include<stdio.h>
#include<stdlib.h>

//init docxit rego
static void docxitInit()
{
	if(system("mkdir -p $PWD/.docxit/object") == -1){  //create folder objects to hold all history version files
        printf("fatal: mkdir failed\n");
        exit(0);
	}
	if(system("touch $PWD/.docxit/HEAD $PWD/.docxit/index") == -1){
        printf("fatal: touch failed\n");
        exit(0);
	}
	if(system("echo $PWD/ >> ~/.docxitPath") == -1){
        printf("fatal: echo failed\n");
        exit(0);
	}
}

int main()
{
  docxitInit();
     printf("Successfully initialize empty Docxit repository\n");
  return 0;
}

