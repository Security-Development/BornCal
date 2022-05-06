#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define _CRT_SECURE_NO_WARNINGS
void error_handling(char *message) {
    fputs(message,stderr);
    fputs("\n",stderr);
    exit(1);
}

int main(int argc, char *argv[]) {
    printf("1\n");
    int serv_sock;
    int clnt_sock;
    //printf("2\n");

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    //printf("3\n");

    char message[]="Hello World!";
    //printf("4\n");

    if (argc!=2) {
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }
    //printf("5\n");

    serv_sock=socket(PF_INET, SOCK_STREAM, 0) ;
    if(serv_sock == -1) error_handling("socket() error");
    //printf("6\n");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    //printf("7\n");

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1) error_handling("bind() error");

    //printf("8\n");

    //printf("81\n");
    while (1) {
        if(listen(serv_sock,5)==-1) error_handling("listen() error");
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
        //printf("82\n");
        if(clnt_sock == -1) {
            printf("Error!");
            error_handling("accept() error");
            break;
        }

        write(clnt_sock, message, sizeof(message));

    }

    close(clnt_sock);
    close(serv_sock);
    printf("0\n");

    return 0;



}




