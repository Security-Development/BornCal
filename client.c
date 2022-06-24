#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct Packet{
    short opcode;
    short data_len;
    char msg[50];
} Packet;

typedef struct claData {
    double num1;
    double num2;
    unsigned int opNum;
} claData;


void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n',stderr);
    exit(1);
}

int main() {
        int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join;
        struct sockaddr_in address;
        Packet packet;
        claData cladata;

        if( !client )
                return 0;

        memset(&address, 0, sizeof(address));
        memset(&packet, 0, sizeof(packet));
        memset(&cladata, 0, sizeof(cladata));

        int portnum = 7904;
        address.sin_port = htons(portnum);
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        cladata.opNum = 6; //opNum. 1:+, 2:-, 3:*, 4:/, 5:result, 6:srvoff
        cladata.num1 = 50; //num1
        cladata.num2 = 10; //num2

        if( (join = connect(client, (struct sockaddr *) &address, sizeof(address))) == -1 )
                return 0;

        printf("[*] Connection Server !!\n");
        sendto(client, &cladata, sizeof(cladata), 0, (struct sockaddr *)&address, sizeof(address));
        printf("[+] Send To Data cladata : 0x%x\n", cladata);
        printf("[+] opNum : %d\n", cladata.opNum);
        printf("[+] num1 : %lf\n", cladata.num1);
        printf("[+] num2 : %lf\n", cladata.num2);


        if (cladata.opNum != 6) {
            //이 아래 문단은 서버로부터 들어오는 결과값을 받습니다. ... The paragraph below receives the resulting value from the server.
            struct sockaddr_in s_addr;  // server ip addr
            struct sockaddr_in c_addr;  // clinet ip addr
            int s_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
            socklen_t c_addr_size;
            memset(&s_addr, 0, sizeof(s_addr)); // socketaddr_in struct initialize
            s_addr.sin_family = AF_INET;
            s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // for server, localhost
            s_addr.sin_port=htons(7905); // listen port#
            if(bind(s_sock, (struct sockaddr*) &s_addr, sizeof(s_addr)) == -1)
                error_handling("bind() error");
            c_addr_size = sizeof(c_addr);
            memset(&cladata, 0, sizeof(cladata));
            int packet_len;
            packet_len = recvfrom(s_sock, &cladata, sizeof(cladata), 0, (struct sockaddr*)&c_addr, &c_addr_size);
            printf("packet_len : %d\n",packet_len);
            printf("result : %lf\n",cladata.num1);
        }

        return 0;
}
