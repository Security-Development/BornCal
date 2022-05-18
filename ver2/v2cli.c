#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
void error_handling(char *message);
int check_ans(char *message);
void stoper();

//cli , client , receiver
//int argc, char *argv[]
//int receiver(char* address, char* port) {
int receiver() {
    char address[100] ;
    char port[6];
    stoper("receiver");
    //argc : arg count
    //argv : arg value

    //argv[1] : address , string
    //argv[2] : port number , string

    int sock;
    struct sockaddr_in serv_addr;

    int str_len;

    /*
    if(argc!=3) {
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }
    */

    int count = 0;
    while (1) {
        time_t start = time(NULL);

        sock=socket(PF_INET, SOCK_STREAM, 0);
        if(sock==-1) error_handling("spclet() error");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        //serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
        serv_addr.sin_addr.s_addr=inet_addr(address);
        //serv_addr.sin_port=htons(atoi(argv[2]));
        serv_addr.sin_port=htons(atoi(port));

        char message[30];
        /*
        while (1) { if ((int)(time(NULL) - start) > 1 && count < 10) {
                count++;
                break;}}
         */
        if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) error_handling("connect() error!");

        str_len=read(sock, message, sizeof(message)-1);
        if(str_len==-1) error_handling("read() error!");
        printf("<Message from server: '%s'> \n",message);
        close(sock);
    }

    return 0;
}

//ser, server, sender
//int argc, char *argv[]
//int sender(char* port) {
int sender() {
    char address[100];
    char port[6];
    //argc : arg count
    //argv : arg value
    stoper("sender");
    //argv[0] : port number , string


    printf("1\n");
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    /*
    if (argc!=2) {
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }
    */
    serv_sock=socket(PF_INET, SOCK_STREAM, 0) ;
    if(serv_sock == -1) error_handling("socket() error");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    //serv_addr.sin_port=htons(atoi(argv[1]));
    serv_addr.sin_port=htons(atoi(port));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1) error_handling("bind() error");


    int userans = 1;
    if(listen(serv_sock,5)==-1) error_handling("listen() error");
    clnt_addr_size = sizeof(clnt_addr);
    printf("time now : %ld\n",clock());
    while (1) {
        char message[30]="";
        printf("입력 :");
        scanf("%s",message);
        write(clnt_sock, message, sizeof(message));
        //이 함수(write)를 사용하면 콘솔에서도 이 평문이 나오게 된다.
        //좀 더 정확히 말하자면, 이 함수를 사용했고, 정상적인 기능의 수행이 실패했을 경우에는 넣었던 메세지(평문)을 다시 출력하는 형태로 반환한다.

        char ti[30];
        sprintf(ti, "%f", ((float)clock()));
        strcat(message,ti);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
        if(clnt_sock == -1) {
            printf("Error!");
            error_handling("accept() error");
            break;
            printf("\n");
        }
        printf("\n");

    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

int main() {
    //7904 port need blocking
    //1. ack to ser by 7904 port
    //2. accept re-ack from ser
    //3. send ops of cli to ser
    //4. regist cli 'account' at ser

    //1. 7904 포트를 이용해서 서버에 접속해도 되는지 물어본다
    //2. 7904 포트를 이용해 서버로부터 승인 신호를 받는다
    //3. 서버에게 지금 접속할 클라이언트의 정보를 보낸다. (공개접속하여 방을 알릴것인지, 아니면 비밀접속하여 내 방번호화 포트번호를 알고있는 사람만 들어올 수 있게 할건지)
    //4. 서버에 클라이언트의 정보를 등록해놓는다.

    //get ans or ops from user after entering funcs
    //(필요한)정보는 함수로 넘어간 다음에 유저로부터 받자. 지금은 멀티스레드(또는 멀티프로세스)기술을 이용하면서 여러개의 변수를 넘길 방법을 알아내지 못했다.
    while(1) {
        printf("sender : s or client\nreciever only : r or server\nget out : b\nans :");
        char ans[20];
        scanf("%s",ans);
        getchar();
        //if (ans=="s" || ans=="client") {
        if (strcmp(ans,"s") || strcmp(ans,"client")) {
            printf("s\n");
            if(check_ans("s")) {
                sender();
            }
        } else if(strcmp(ans,"r") || strcmp(ans,"server")) {
            printf("r\n");
            if(check_ans("s")) {
                receiver();
            }
        } else if(strcmp(ans,"b")) {
            printf("b? break! escape!\n");
            break;
        } else {
            printf("ans was '%s'\n",ans);
        }
        printf("\n\n");
    }


}

void error_handling(char *message) {
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int check_ans(char *message) {
    getchar();
    while(1) {
        printf("%s right? (Y / N) :",message);
        char ans;
        scanf("%c",&ans);
        getchar();
        if(ans=='Y') {
            return 1;
        } else if(ans=='N') {
            return 0;
        } else {
            printf("Y or N plz\n");
        }
    }
}

void stoper(char* mssg) {
    char ans[100];
    printf("Enter anything for KeepGoing(%s)",mssg);
    scanf("%s",ans);
    //free(ans);
}