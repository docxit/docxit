#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include "mergeRecords.h"

#define SERVPORT 0xd0c   //port number
#define BACKLOG 10//请求队列中允许的最大请求数

#define MAXDATASIZE 500000000//数据长度 最多 500 M

using namespace std;

int main(int argc, char *argv[])
{
    int sin_size,recvbytes;
    int sockfd,client_fd;       //socket描述符
    struct sockaddr_in server_sockaddr;
    struct sockaddr_in client_sockaddr;

    char *buf;
    if((buf = (char *)malloc(sizeof(char) * MAXDATASIZE)) == NULL){
        printf("fatal: malloc failed for 500 MB\n");
        exit(0);
    }

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1) {//建立socket链接
        perror("Socket");
        exit(1);
    }

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(SERVPORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);

//    int on = 1;
//    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0){
//        perror("setsockopt");
//        exit(1);
//    }
    if((bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr))) == -1) {//bind函数绑定
        perror("bind");
        exit(-1);
    }

    if(listen(sockfd,BACKLOG) == -1) {//监听
        perror("listen");
        exit(1);
    }

    printf("ready to receive, listening ...\n");

    if((client_fd = accept(sockfd,(struct sockaddr *) &client_sockaddr,(socklen_t *)&sin_size)) == -1) {//等待客户端链接
        perror("accept");
        exit(1);
    }


    if((recvbytes = recv(client_fd,buf,MAXDATASIZE,0)) == -1) {//接收客户端的请求
        perror("recv");
        exit(1);
    }

    printf("receive from %s, press Y to continue   (Y / N) ",buf);
    fflush(stdin);
    int yn = getchar();

    if(yn != 'Y' && yn != 'y'){
        if(send(client_fd,"NO",3,0) == -1){
            perror("send");
            exit(1);
        }
        printf("exit from the connection\n");
    }
    else{
        string ack = "OK"s + argv[1];   // OK<path>
        if(send(client_fd,ack.c_str(),ack.size() + 1,0) == -1){
            perror("send");
            exit(1);
        }
        printf("receiving data ...\n");

        if((recvbytes = recv(client_fd,buf,MAXDATASIZE,0)) == -1) {//接收客户端的请求
            perror("recv");
            exit(1);
        }
        if(recvbytes == 0){
            printf("error: receive nothing\n");
            exit(0);
        }
        std::string path = argv[1];
        path = path + "docxitremote.tar.gz";
        FILE *fp = fopen(path.c_str(), "wb");
        if(fp == NULL){
            printf("fatal: open package failed\n");
            exit(0);
        }

        fwrite(buf, recvbytes, 1, fp);
        fclose(fp);
        printf("dispackaging ...\n");
        string cd = "cd "s + argv[1] + ";tar -zxf docxitremote.tar.gz;rm -f docxitremote.tar.gz";
        if(system(cd.c_str()) == -1){
            printf("fatal: extract failed\n");
            exit(0);
        }
        printf("merging ...\n");
        mergeRecords(argv[1] + ".docxit/index"s, argv[1] + ".docxit/indexre"s, "local"s, "remote"s, argv[1]);
    }
    close(sockfd);
    free(buf);
    return 0;
}
