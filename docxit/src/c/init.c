#include<stdio.h>
#include<stdlib.h>

//init docxit rego
void docxitInit()
{
  system("mkdir $PWD/.docxit");//creat rego
  system("mkdir $PWD/.docxit/object");//create folder objects to hold all history version files
	system("touch $PWD/.docxit/HEAD");//create file HEAD to hold current version pointer
	system("touch $PWD/.docxit/index");//create file index to be the stage
 system("echo $PWD/ >> ~/.docxitPath");
}

int main()
{
  docxitInit();
     printf("Successfully initialize empty Docxit repository\n");
  return 0;
}

