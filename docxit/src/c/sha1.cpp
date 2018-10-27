#include"sha1.h"
#include"shellCommand.h"

string valueSHA_1(string filename)
{
    string command = "sha1sum $PWD/" + filename;
    string value_sha1;
    value_sha1 = shellCommand(command);
    value_sha1 = value_sha1.substr(0,40);
    return value_sha1;
}
