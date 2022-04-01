#include <iostream>
#include <sys/socket.h>

/***
   * return sucess => 1 || faild => 0
   */
int main() {
	int server;
	
	/***
	   * TCP => SOCK_STREAM
	   * UDP => SOCK_DGRAMA
	   * IPv4 Protocol => AF_INET
	   * IPv6 Protocol => AF_INET6
	   */
	if( (server = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
		return 0; //could not create server
		
		
		
		
	return 1;
}
