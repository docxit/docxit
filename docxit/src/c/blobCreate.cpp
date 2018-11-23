#include"docxitPath.h"
#include"blobCreate.h"

//create a blob object to the file depending on it's sha-1 value
void blobCreate(string filename, string value_sha1)//0 = no blob obj, 1 = exist blob obj
{
  //[ -f filename ] ||
  string path = DOCXIT_PATH + ".docxit/object/";
  cout << path << endl;
  string foldername = path + value_sha1.substr(0,2);//take the head 2 numbers for folder name
  string blobname = foldername + '/' + value_sha1.substr(2,38);//take the last 38 numbers for the blob object name
  string mkdir = "mkdir -p " + foldername;
<<<<<<< HEAD
  string cp = "cp $PWD/" + filename + " " + blobname;
  string command;
  command = mkdir;
  command = command + " ; " + cp;
  system(command.c_str());
}

int main()
{
     blobCreate("test.pl", "da39a3ee5e6b4b0d3255bfef95601890afd80709");
}
=======
  //string cp = "cp $PWD/" + filename + " " + blobname;
  string cp = "cp " + filename + " " + blobname;
  string command = "[  -f " + blobname + "  ]";
  command = command + " || " + mkdir;
  command = command + " && " + cp;
  system(command.c_str());
}

>>>>>>> yxy





