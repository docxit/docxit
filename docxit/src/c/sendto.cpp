#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;
#include "configOp.h"
#include "indexOp.h"

#define SERVPORT 0xd0c
#define MAXDATASIZE 500000000   // 500 M

#define USAGE "\
Usage: docxit sendto <remote_user_name>             send to user (in config)\n\
                     -ip <ip>                       send to specific ip address\n\
\n\
the remote user should first execute `docxit listen`\n\
"

static void package(string path){
    printf("packaging ...\n");
    string cmd = "cd " + path + ";cp .docxit/index .docxit/indexre;tar -zcf docxitremote.tar.gz .docxit/indexre";
    string indexp = path + ".docxit/index";
    Records rec = openIndex(indexp.c_str());

    for(int i = 0; i < rec.length; i ++){
        if(rec.base[i].kind != unchanged){
            printf("error: please commit before sending\n");
            exit(0);
        }
        string key = rec.base[i].key;
        cmd = cmd + " .docxit/object/" + key.substr(0,2) + '/' + key.substr(2,38);
    }
    if(system(cmd.c_str()) == -1){
        printf("fatal: packing failed\n");
        exit(0);
    }
}

int main(int argc,char *argv[]) {

    string addr = "";

    if(argc < 3) {
        printf("%s", USAGE);
        exit(0);
    }
    else if(argc == 3) {
        addr = getIPbyUserName(argv[2], configpath());
    }
    else if(!strcmp(argv[2], "-ip")) addr = argv[3];
    else  {
        printf("%s", USAGE);
        exit(0);
    }

    string username = getUserName(configpath());

    int sockfd,sendbytes;
    char *buf;
    if((buf = (char *)malloc(sizeof(char) * MAXDATASIZE)) == NULL){
        printf("fatal: malloc failed for 500 MB\n");
        exit(0);
    }
    struct sockaddr_in serv_addr;


    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1) {//创建socket
        perror(addr.c_str());
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVPORT);
    serv_addr.sin_addr.s_addr = inet_addr(addr.c_str());
    bzero(&(serv_addr.sin_zero),8);

    if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))) == -1) {//发起对服务器的链接
        perror(addr.c_str());
        exit(1);
    }

    if((sendbytes = send(sockfd,username.c_str(),username.size() + 1,0)) == -1) {//发送消息给服务器端
        perror(addr.c_str());
        exit(1);
    }

    printf("waiting for the server to confirm ...\n");

    char buf2[10];
    if(recv(sockfd,buf2,10,0)== -1) {
        perror(addr.c_str());
        exit(1);
    }

    if(strcmp(buf2, "OK")){
        printf("your connection has be rejected, exiting\n");
    }
    else{
        package(argv[1]);
        string path = argv[1];
        path = path + "docxitremote.tar.gz";
        FILE *fp = fopen(path.c_str(), "rb");
        if(fp == NULL){
            printf("fatal: open package failed\n");
            exit(0);
        }
        if(fread(buf, 1, MAXDATASIZE, fp) == 0) {
            printf("fatal: read file error\n");
            exit(0);
        }

        if((sendbytes = send(sockfd,buf,ftell(fp),0)) == -1) {//发送消息给服务器端
            perror(addr.c_str());
            exit(1);
        }
        string rm = "rm -f " + path + " " + argv[1] + ".docxit/indexre";
        if(system(rm.c_str()) == -1){
            printf("fatal: rm failed\n");
            exit(0);
        };

        fclose(fp);
    }
    close(sockfd);
    free(buf);
    return 0;
}
