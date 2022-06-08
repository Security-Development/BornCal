#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_MSG_SIZE 50

const unsigned int header_len = sizeof(short)*2;

struct Packet{
    short opcode;
    short data_len;
    char msg[MAX_MSG_SIZE];
};

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc, char  *argv[]){
    int sock;
    short id;

    struct sockaddr_in s_addr;
    struct Packet packet;

    char msg[MAX_MSG_SIZE];
    int str_len;

    if(argc!=4){
        printf("Usage : %s <ID> <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1)
        error_handling("socket() error");

    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(argv[2]);
    s_addr.sin_port=htons(atoi(argv[3]));
    id = htons(atoi(argv[1]));

    // for connected UDP
    // if(connect(sock, (struct sockaddr*) &s_addr, sizeof(s_addr)) == -1)
    //    error_handling("connect() error");

    while(1){
        printf("Destination Server: %s:%d\n", inet_ntoa(s_addr.sin_addr), ntohs(s_addr.sin_port));

        str_len = scanf("%s", msg);

        if(str_len == -1)
            error_handling("read() error");
        if(!strcmp(msg, "!FIN"))
            break;

        memset(&packet, 0, sizeof(packet));
        packet.opcode = 101;
        packet.data_len = strlen(msg)+1;
        strcpy(packet.msg, msg);

        sendto(sock, &packet, header_len + sizeof(char)*packet.data_len, 0, (struct sockaddr*)&s_addr, sizeof(s_addr));

        printf("Send Message to %s:%d: %s\n", inet_ntoa(s_addr.sin_addr), ntohs(s_addr.sin_port), packet.msg);
    }
    printf("Connection Finished.\n");

    close(sock);

    return 0;
}
