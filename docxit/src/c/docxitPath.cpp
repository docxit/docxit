#include"docxitPath.h"

static int LineLength = 100;
string DOCXIT_PATH;//= path + '/'

int docxitPath()
{
  ifstream fh("/home/pwtm/.docxitinfo");//open root_directory-restoring file
  if(!fh)
  {
      cout<< "open d_info failed" << endl;
      return 0;
  }
  char StrLine[LineLength];
  string cont;
  system("echo $PWD/ >> pwd ");
  ifstream pwd("./pwd");//create pwd to save $PWD
  pwd.getline(StrLine, LineLength);
  cont = StrLine;//cont = $PWD
  system("rm ./pwd");// delete pwd
  int suc_sig = 0;
  while(fh.getline(StrLine, LineLength))//find the root directory, the r_directory is head part of $PWD
  {
      if(cont.find(StrLine) == 0)
      {
          suc_sig = 1;
          DOCXIT_PATH = StrLine;
          break;
      }
  }
  return suc_sig;
}

int main()
{
    docxitPath();
    cout << DOCXIT_PATH << endl;
}
