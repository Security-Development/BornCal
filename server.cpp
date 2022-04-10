#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 9999
#define MAXIMUN_LENGTH 8
#define MAX_BUFF 512

using namespace std;

/***
   * return sucess => 1 || faild => 0
   */
int main(int argc, char const *argv[]) {
        int server, connect;
        sockaddr_in ipv4;
        char rBuff[MAX_BUFF] = {0}; // recive Buffer

        ipv4.sin_family = AF_INET; // ipv4 change
        ipv4.sin_addr_s_addr = INADDR_ANY; // Allow anyone to access the server
        ipv4.sin_port = htons(5000); // port setting

        /***
           * TCP => SOCK_STREAM
           * UDP => SOCK_DGRAMA
           * IPv4 Protocol => AF_INET
           * IPv6 Protocol => AF_INET6
           */
        if( (server = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
        if( (connect = bind(server, (struct sockaddr *) &ipv4, sizeof(ipv4))) < 0 )
        if( listen(server, MAXIMUN_LENGTH) < 0 )
                return 0; //could not create server

        // IPV4 Info Print
        char *pIp = inet_ntoa(ipv4.sin_addr);
        uint16_t pPort = htons(ipv4.sin_port);
        printf("Suscess Create Server\nAddress : %s\nPort : %d", pIp, pPort);



        return 1;
}
