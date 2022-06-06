
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

int main(int argc, char* argv[])
{
    int sock;

    short Sequence_Number = 0;
    short Acknowledge_Number = 0;

    struct sockaddr_in serv_addr;
    int server_addr_size;
    char sendBuff[BUFF_SIZE];
    char readBuff[BUFF_SIZE];
    ssize_t receivedBytes;
    ssize_t sentBytes;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    inet_aton("127.0.0.1",(struct in_addr*)&serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(20162);
    // 소켓 생성
    if ((sock = socket(PF_INET,SOCK_DGRAM, 0))==-1)
        {
        printf("socket 생성 실패\n");
        exit(0);
        }
    while (1) {
        // 채팅 프로그램 제작
        server_addr_size = sizeof(serv_addr);
        //클라이언트에서 메세지 전송
        printf("클라이언트에서 보낼 말을 입력하세요 :: ");

        char msg[BUFF_SIZE];
        fgets(msg, BUFF_SIZE, stdin);
        memset(&Sequence_Number,0,sizeof(Sequence_Number));
        //need add codes here
        sprintf(sendBuff,"%s"+(char*)Sequence_Number+(char*)Acknowledge_Number,msg);
        sentBytes = sendto(sock,sendBuff,strlen(sendBuff),0,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
        receivedBytes = recvfrom(sock,readBuff,BUFF_SIZE,0,(struct sockaddr*)&serv_addr, &server_addr_size);
        printf("%lu bytes read\n", receivedBytes);
        //전송 매개 변수인 readBuff을 이렇게 정리하지 않으면 이따금씩 1바이트단위로 상대방에게 보내져버린다.
        readBuff[receivedBytes] = '\0';
        //이 fputs 함수의 사용 의도는 정리하는것보다는 자신이 어떤 정보를 보냈는지 다시 알려주는 역할로 추정된다.
        //fputs(readBuff,stdout);
        fflush(stdout);
        }
    // 소켓 close
    close(sock);
    return 0;
}






