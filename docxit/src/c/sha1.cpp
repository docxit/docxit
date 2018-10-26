#include"sha1.h"

string valueSHA_1(string filename)
{
    int pipefd[2];
    pipe(pipefd);
    int fd;
    fd = dup(STDOUT_FILENO);//save handle of file stdout
    dup2(pipefd[1], STDOUT_FILENO);//STDOUT -> pipefid[1]; pipefid[1] is write port
    string command = "sha1sum $PWD/" + filename;
    system(command.c_str());
    close(pipefd[1]);
    void *buffer = malloc(sizeof(char)*45);
    read(pipefd[0], buffer, 44);
    close(pipefd[0]);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    //
    ((char *)buffer)[40] = '\0';
    string value_sha1 = (char *)buffer;
    free(buffer);
    return value_sha1;
}

int main()
{
    string res = valueSHA_1("sha1.h");
    cout << res << endl;
}

