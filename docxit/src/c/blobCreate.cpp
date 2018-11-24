#include"blobCreate.h"

//create a blob object to the file depending on it's sha-1 value
void blobCreate(string filename, string value_sha1, const char *docxitrootpath)
{
  //[ -f filename ] ||
  string DOCXIT_PATH = docxitrootpath;
  string path = DOCXIT_PATH + ".docxit/object/";
  string foldername = path + value_sha1.substr(0,2);//take the head 2 numbers for folder name
  string blobname = foldername + '/' + value_sha1.substr(2,38);//take the last 38 numbers for the blob object name
  string mkdir = "mkdir -p " + foldername;
  //string cp = "cp $PWD/" + filename + " " + blobname;
  string cp = "cp " + filename + " " + blobname;
  string command = "[  -f " + blobname + "  ]";
  command = command + " || " + mkdir;
  command = command + " && " + cp;
  system(command.c_str());

}
void blobCreateMv(string filename, string value_sha1, const char *docxitrootpath)
{
  //[ -f filename ] ||
  string DOCXIT_PATH = docxitrootpath;
  string path = DOCXIT_PATH + ".docxit/object/";
  string foldername = path + value_sha1.substr(0,2);//take the head 2 numbers for folder name
  string blobname = foldername + '/' + value_sha1.substr(2,38);//take the last 38 numbers for the blob object name
  string mkdir = "mkdir -p " + foldername;
  //string cp = "cp $PWD/" + filename + " " + blobname;
  string cp = "mv " + filename + " " + blobname;
  string command = "[  -f " + blobname + "  ]";
  command = command + " || " + mkdir;
  command = command + " && " + cp;
  system(command.c_str());

}






