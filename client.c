#include <stdio.h>
#include <string.h>
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
        int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join, size, result = 0;
        char buff[50] = "12";
        struct sockaddr_in address;
        Packet packet;
        claData cladata;

        if( !client )
                return 0;

        memset(&address, 0, sizeof(address));
        memset(&packet, 0, sizeof(packet));
        memset(&cladata, 0, sizeof(cladata));

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        //address.sin_port = htons(9123);
        address.sin_port = htons(7904);

        /*
        packet.opcode = 1;
        packet.data_len = sizeof(buff);
        strcpy(packet.msg, buff);
        */
        cladata.opNum = 1;
        cladata.num1 = 50;
        cladata.num2 = 10;

        if( (join = connect(client, (struct sockaddr *) &address, sizeof(address))) == -1 )
                return 0;

        printf("[*] Connection Server !!\n");

        //sendto(client, &packet, sizeof(packet), 0, (struct sockaddr *)&address, sizeof(address));
        sendto(client, &cladata, sizeof(cladata), 0, (struct sockaddr *)&address, sizeof(address));

        //printf("[+] Send To Data Packet : 0x%x\n", packet);
        printf("[+] Send To Data cladata : 0x%x\n", cladata);
        /*
        printf("[+] opcode : %d\n", packet.opcode);
        printf("[+] data_len : %d\n", packet.data_len);
        printf("[+] msg : %s\n", packet.msg);
        */
        printf("[+] opNum : %d\n", cladata.opNum);
        printf("[+] num1 : %lf\n", cladata.num1);
        printf("[+] num2 : %lf\n", cladata.num2);




        return 0;
}
