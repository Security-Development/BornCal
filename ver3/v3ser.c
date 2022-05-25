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
    struct sockaddr_in serv_addr, clnt_addr;
    int serv_sock, clnt_sock;
    int client_addr_size;

    ssize_t receivedBytes;
    ssize_t sentBytes;
    socklen_t clnt_addrLength = 0;

    memset(&serv_addr,0,sizeof(serv_addr));//memset : 메모리를 정해진 문자로 채운다.
    memset(&clnt_addr,0,sizeof(clnt_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //ser.c : serv_addr.sin_port=htons(atoi(argv[1]));
    serv_addr.sin_port = htons(20162); // 20162 : port number

    //서버소켓생성 및 서버 주소와 bind
    // 서버 소켓 생성(UDP니 SOCK_DGRAM을 이용)
    if ((serv_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  //SOCK_DGRAM:UDP
    {
        printf("Sever:can not Open Socket\n");
        exit(0);
    }
    //bind 과정
    if (bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("Server : can not bind local address");
        exit(0);
    }
    printf("Server:waiting connection request.\n");
    while (1) {//클라이언트 IP 확인
        struct sockaddr_in connectSocket;
        //not found object 'connectSocket' from ser.c codes
        socklen_t connectSocketLength = sizeof(connectSocket);
        //connectSocket 은 sockaddr_in 의 크기(Lenght)를 측정하기 위해 만들어진듯 하다.
        getpeername(clnt_sock,(struct sockaddr*)&clnt_addr,&connectSocketLength);
        char clientIP[sizeof(clnt_addr.sin_addr) + 1] = { 0 };

        sprintf(clientIP,"%s",inet_ntoa(clnt_addr.sin_addr));
        // 접속이 안되었을 때는 while에서 출력 x

        /*
        if(strcmp(clientIP,"0.0.0.0") != 0)
            printf("Client:%s\n",clientIP);
        */
        //채팅 프로그램 제작=
        client_addr_size = sizeof(clnt_addr);
        //recvfrom : 수신함수
        receivedBytes = recvfrom(serv_sock, readBuff, BUFF_SIZE, 0,
                                 (struct sockaddr*)&clnt_addr,&client_addr_size);
        printf("%lu bytes read 1\n",receivedBytes);
        //ex : 5 bytes read

        readBuff[receivedBytes]='\0';
        // 상수(define)으로 정해진 BUFFER_SIZE 사용자 생성 상수에 따라 4096비트의 크기를 가진 readBuff 변수의 끝에 배열종료문자인 '\0'을 삽입함으로써 끝을 정해준다.
        // readBuff 변수를 마무리함으로써 출력할 준비를 마친다는 뜻이다.
        fputs(readBuff,stdout);
        printf("%lu bytes read 2\n",receivedBytes);
        fflush(stdout);


        //fflush 를 통해 사용한 readBuff 변수를 다시 청소해준다.
        sprintf(sendBuff,"%s",readBuff);

        //마지막에 이 sendto 함수를 통해서 다시 값을 반환함으로써 cli가 다시금 전송을 할 수 있게 해주는거같다.
        sentBytes = sendto(serv_sock, sendBuff, strlen(sendBuff), 0,(struct sockaddr*)&clnt_addr, sizeof(clnt_addr));
    }
    //서버 소켓 close
    close(serv_sock);
    return 0;
}


