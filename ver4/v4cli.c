#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//수신자
typedef struct Player_Socket {
    float x, y, z;
    float camxrotate, camyrotate;
    int live; //bool
    int team; //bool
    char nickName[16];
    int character_down_state;
}Player_Socket;
Player_Socket player;

Player_Socket recv_Player(SOCKET sock) {
    int retval;
    int len;
    int sock;
    retval = recvn(sock, (char*)&len, sizeof(int), 0); // 데이터 받기(고정 길이)
    if (retval == SOCKET_ERROR) {
        err_display("recv()");
    }
    int GetSize;
    char suBuffer[BUFSIZE];
    Player_Socket* player;
    GetSize = recv(sock, suBuffer, len, 0);
    if (GetSize == SOCKET_ERROR) { exit(1); }
    suBuffer[GetSize] = '\0';
    player = (Player_Socket*)suBuffer;
    return *player;
}

int main() {

    recv_Player();
}