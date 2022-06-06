#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
void error_handling(char *message);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;

    int str_len;

    if(argc!=3) {
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }
    int count = 0;
    while (1) {
        time_t start = time(NULL);

        //sock=socket(PF_INET, SOCK_STREAM, 0);
        sock=socket(PF_INET, SOCK_DGRAM, 0);
        if(sock==-1) error_handling("spclet() error");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
        serv_addr.sin_port=htons(atoi(argv[2]));

        char message[30];
        /*
        while (1) { if ((int)(time(NULL) - start) > 1 && count < 10) {
                count++;
                break;}}
         */
        printf("Ready Accept\n");
        printf("break1\n");
        while (1) {
            printf("break2\n");
            if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
                char arrans[30];
                printf("con err\n");
                scanf("%s",arrans);
                //error_handling("connect() error!");
                continue;
            } else {
                break;
            }

        }

        str_len=read(sock, message, sizeof(message)-1);
        if(str_len==-1) error_handling("read() error!");
        printf("<Message from server: '%s'> \n",message);
        close(sock);
    }

    return 0;
}

void error_handling(char *message) {
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
