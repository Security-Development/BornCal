#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
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

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc!=2) {
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    serv_sock=socket(PF_INET, SOCK_STREAM, 0) ;
    if(serv_sock == -1) error_handling("socket() error");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1) error_handling("bind() error");

    while (1) {
        char ti[30];
        sprintf(ti, "%f", ((float)clock()));
        char message[30]="Hello World!";
        strcat(message,ti);
        int userans = 1;
        if(listen(serv_sock,5)==-1) error_handling("listen() error");
        clnt_addr_size = sizeof(clnt_addr);
        printf("time now : %ld",clock());
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
        if(clnt_sock == -1) {
            printf("Error!");
            error_handling("accept() error");
            break;
        }

        write(clnt_sock, message, sizeof(message));
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}




