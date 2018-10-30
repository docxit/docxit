#include"docxitPath.h"
#include"shellCommand.h"

string DOCXIT_PATH;//= path + '/'

int docxitPath()//0 = failed, 1 = find parent path, 2 = find child path
{
  string filecont = shellCommand("[ -f ~/.docxitPath ] || touch ~/.docxitPath : cat ~/.docxitPath");
  string curpath = shellCommand("echo $PWD");
  curpath = curpath.substr(0, curpath.length() - 1) + '/';
  //cout << "curpath " << curpath << endl;
  int pos = filecont.find("\n", 0);
  string line;
  int signal = 0;
  while(pos != -1)
  {
      line = filecont.substr(0, pos);
      //cout << "line " << line << endl;
      if(curpath.find(line) == 0)
      {
          signal = 1;
          DOCXIT_PATH = line;
          break;
      }
      else if(line.find(curpath) == 0)
      {
          signal = 2;
          break;
      }
      filecont = filecont.substr(pos + 1, filecont.length());
      //cout << "filecont " << filecont <<endl;
      pos = filecont.find("\n", 0);
  }
  return signal;
}

