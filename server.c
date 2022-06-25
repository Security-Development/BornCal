//main writer : hjm , ysc
//first version file from /ver2/u_sv.c (git commit number : c9cccf157918fc91a380594591e03a72d0a08b8f)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const unsigned int header_len = sizeof(short)*2;

typedef struct Packet{
    short opcode;
    short data_len;
    char msg[50];
} Packet;

typedef struct claData {
    int opNum;
    double num1;
    double num2;
    double result; // 결과값 저장
} claData;

#define MAX_MSG_SIZE 50

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n',stderr);
    exit(1);
}

double cal(claData cladata){            // calculate in accordance with claData
    int n_point = 1;
    switch(cladata.opNum)
    {
        case 1:
            return cladata.num1 + cladata.num2;

        case 2:
            return cladata.num1 - cladata.num2;

        case 3:
            while (1)
            {
                if ( fmod(cladata.num1, 1.0f) == 0 && fmod(cladata.num2, 1.0f) == 0)
                    break;
                cladata.num1 *= 10;
                cladata.num2 *= 10;
                n_point *= 100;
            }
            return cladata.num1 * cladata.num2 / n_point;

        case 4:
            while (1)
            {
                if ( fmod(cladata.num1, 1.0f) == 0 && fmod(cladata.num2, 1.0f) == 0)
                    break;
                cladata.num1 *= 10;
                cladata.num2 *= 10;
                n_point *= 100;
            }
            return cladata.num1 / cladata.num2 / n_point;
    }
}

int main(int argc, char  *argv[]){
    while(1) {

        int s_sock; // listening port

        struct sockaddr_in s_addr;  // server ip addr
        struct sockaddr_in c_addr;  // clinet ip addr
        struct claData cladata;
        socklen_t c_addr_size;

        char msg[MAX_MSG_SIZE];
        int msg_len;
        int packet_len;
        double answer;


        if (argc != 2) {
            printf("Usage : %s <port>\n", argv[0]);
            exit(1);
        }

        s_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (s_sock == -1)
            error_handling("socket() error");

        memset(&s_addr, 0, sizeof(s_addr)); // socketaddr_in struct initialize
        s_addr.sin_family = AF_INET;
        s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // for server, localhost
        s_addr.sin_port = htons(atoi(argv[1])); // listen port#

        if (bind(s_sock, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) // bind port & ip to socket
            error_handling("bind() error");
        while (1) {   // server will not closes after client disconnect.
            while (1) {
                c_addr_size = sizeof(c_addr);
                memset(&cladata, 0, sizeof(cladata));
                //msg_len = recvfrom(s_sock, &cladata, sizeof(cladata), 0, (struct sockaddr*)&c_addr, &c_addr_size);
                packet_len = recvfrom(s_sock, &cladata, sizeof(cladata), 0, (struct sockaddr *) &c_addr, &c_addr_size);
                if (packet_len == -1 && strcmp(inet_ntoa(c_addr.sin_addr), "0.0.0.0")) {
                    error_handling("recvfrom() error");
                    continue;
                } else {
                    break;
                }
            }
            if (cladata.opNum == 6.0) {
                return 0;
            }
            answer = cal(cladata);
            //sleep(1);
            struct sockaddr_in address;
            memset(&cladata, 0, sizeof(cladata));
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = inet_addr("127.0.0.1");
            address.sin_port = htons(7905);
            cladata.opNum = 5;
            cladata.num1 = answer;
            cladata.num2 = answer;
            int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join, size, result = 0;
            if ((join = connect(client, (struct sockaddr *) &address, sizeof(address))) == -1)
                return 0;
            sendto(client, &cladata, sizeof(cladata), 0, (struct sockaddr *) &address, sizeof(address));


        }
    }
    return 0;
}

