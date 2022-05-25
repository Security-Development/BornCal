#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 20162
#define BUFFER_SIZE 4096//서버에 이용
#define BUFF_SIZE 100//클라이언트에 이용

//server.cpp
int main(int argc,char *argv[])
{
 char readBuff[BUFFER_SIZE];
 char sendBuff[BUFFER_SIZE];
 struct sockaddr_in serverAddress, clientAddress;
 int server_fd, client_fd;
 int client_addr_size;
 ssize_t receivedBytes;
 ssize_t sentBytes;
 socklen_t clientAddressLength = 0;
 memset(&serverAddress,0,sizeof(serverAddress));
 memset(&clientAddress,0,sizeof(clientAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
 serverAddress.sin_port = htons(20162);
 //서버소켓생성 및 서버 주소와 bind
 // 서버 소켓 생성(UDP니 SOCK_DGRAM이용)
 if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  //SOCK_DGRAM:UDP
     {
        printf("Sever:can not Open Socket\n");
        exit(0);
     }
 //bind 과정
 if (bind(server_fd,(struct sockaddr *)&serverAddress,sizeof(serverAddress)) < 0)
     {
     printf("Server : can not bind local address");
     exit(0);
     }
printf("Server:waiting connection request.\n");
 while (1) {//클라이언트 IP 확인
     struct sockaddr_in connectSocket;
     socklen_t connectSocketLength = sizeof(connectSocket);
     getpeername(client_fd,(struct sockaddr*)&clientAddress,&connectSocketLength);
     char clientIP[sizeof(clientAddress.sin_addr) + 1] = { 0 };
     sprintf(clientIP,"%s",inet_ntoa(clientAddress.sin_addr));
     // 접속이 안되었을 때는 while에서 출력 x
     if(strcmp(clientIP,"0.0.0.0") != 0)
         printf("Client:%s\n",clientIP);
     //채팅 프로그램 제작
     client_addr_size = sizeof(clientAddress);
     receivedBytes = recvfrom(server_fd, readBuff, BUFF_SIZE, 0, (struct sockaddr*)&clientAddress,&client_addr_size);
     printf("%lu bytes read\n",receivedBytes);
     readBuff[receivedBytes]='\0';
     fputs(readBuff,stdout);
     fflush(stdout);
     sprintf(sendBuff,"%s",readBuff);
     sentBytes = sendto(server_fd, sendBuff, strlen(sendBuff), 0,(struct sockaddr*)&clientAddress, sizeof(clientAddress));
 }
 //서버 소켓 close
 close(server_fd);
 return 0;
}


