#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct Packet{
    short opcode;
    short data_len;
    char msg[50];
} Packet;

int main() {
        int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join, size, result;
        char buff[50] = "12";
        struct sockaddr_in address;
        Packet packet;

        if( !client )
                return 0;

        memset(&address, 0, sizeof(address));
        memset(&packet, 0, sizeof(packet));

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_port = htons(9123);

        packet.opcode = 1;
        packet.data_len = sizeof(buff);
        strcpy(packet.msg, buff);

        if( (join = connect(client, (struct sockaddr *) &address, sizeof(address))) == -1 )
                return 0;

        printf("[*] Connection Server !!\n");

        sendto(client, &packet, sizeof(packet), 0, (struct sockaddr *)&address, sizeof(address));

        printf("[+] Send To Data Packet : 0x%x\n", packet);
        printf("[+] opcode : %d\n", packet.opcode);
        printf("[+] data_len : %d\n", packet.data_len);
        printf("[+] msg : %s\n", packet.msg);

        size = sizeof(address);
        recvfrom(client, &result, sizeof(result), 0, (struct sockaddr *)&address, (int *)&size);
        printf("[+] Server Calculated Value : %d\n", result);


        return 0;
}
