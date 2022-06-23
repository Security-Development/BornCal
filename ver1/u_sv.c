#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const unsigned int header_len = sizeof(short)*2;

struct Packet{
    short opcode;
    short data_len;
    char msg[50];
};

#define MAX_MSG_SIZE 50

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc, char  *argv[]){
    int s_sock; // listening port

    struct sockaddr_in s_addr;  // server ip addr
    struct sockaddr_in c_addr;  // clinet ip addr
    struct Packet packet;
    socklen_t c_addr_size;

    char msg[MAX_MSG_SIZE];
	int msg_len;
	

    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    s_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(s_sock == -1)
        error_handling("socket() error");
    
    memset(&s_addr, 0, sizeof(s_addr)); // socketaddr_in struct initialize
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // for server, localhost
    s_addr.sin_port=htons(atoi(argv[1])); // listen port#

    if(bind(s_sock, (struct sockaddr*) &s_addr, sizeof(s_addr)) == -1) // bind port & ip to socket
        error_handling("bind() error");

    while(1){	// server will not closes after client disconnect.
		while(1){
		sleep(1);
            c_addr_size = sizeof(c_addr);
            memset(&packet, 0, sizeof(packet));
			msg_len = recvfrom(s_sock, &packet, sizeof(packet), 0, (struct sockaddr*)&c_addr, &c_addr_size);

            if (msg_len == -1 && strcmp(inet_ntoa(c_addr.sin_addr), "0.0.0.0")){
                	error_handling("recvfrom() error");
                	continue;
                }

			if(!strcmp(packet.msg,"!DISCON") || !strcmp(packet.msg,"!EXIT")){
				break;
            }
            printf("Message from %s:%d: %s(%d)\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port), packet.msg,  packet.opcode);
		}
        if(!strcmp(packet.msg,"!DISCON")){
            printf("Client Disconnected: %s\n", inet_ntoa(c_addr.sin_addr));
		}
	else if(!strcmp(packet.msg,"!EXIT")){
            printf("Server Terminated by %s\n", inet_ntoa(c_addr.sin_addr));
			break;
		}
    }
    close(s_sock);

    return 0;
}
