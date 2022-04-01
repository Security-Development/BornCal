#include <iostream>
#include <sys/socket.h>

#define PORT 9999

/***
   * return sucess => 1 || faild => 0
   */
int main() {
	int server, connect;
	struct sockaddr_in address;
	
	/***
	   * TCP => SOCK_STREAM
	   * UDP => SOCK_DGRAMA
	   * IPv4 Protocol => AF_INET
	   * IPv6 Protocol => AF_INET6
	   */
	if( (server = socket(AF_INET, SOCK_DGRAM, 0)) == 0 )
		return 0; //could not create server
		
	if( (connect = bind(server, (struct sockaddr *) &address, sizeof(address))) < 0 ); 
		return 0; //could not buid server
		
		
		
		
	return 1;
}
