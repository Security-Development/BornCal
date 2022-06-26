//main writer : hjm , ysc
//first version file from /ver2/u_sv.c (git commit number : c9cccf157918fc91a380594591e03a72d0a08b8f)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const unsigned int header_len = sizeof(short)*2;

typedef struct Packet{
    short opcode;
    short data_len;
    char msg[50];
} Packet;

/*
typedef struct claData {
    int opNum;
    double num1;
    double num2;
    double result; // ê²°ê³¼ê°’ ì €ì¥
} claData;*/

typedef struct _clacData 
{
	int opNum; // + - * / result srvoff, 1 2 3 4 5 6 
 
	int flagnum1;  // int, double, none 1 2 3
	int flagnum2; // int, double, none 1 2 3

	int inum1; // iìˆ«ì1
	int inum2; // iìˆ«ì2
 
	double dnum1;  // dìˆ«ì1
	double dnum2; // dìˆ«ì2
 
	int flagresult;  // int, double, none 1 2 3 

	int iresult; // iê²°ê³¼ ê°’
	double dresult; // dê²°ê³¼ ê°’
}_clacData;

#define MAX_MSG_SIZE 50

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n',stderr);
    exit(1);
}
 
_clacData cal(_clacData cladata){            // calculate in accordance with claData
    int n_point = 1;
	struct _clacData cla_return = cladata;
	double num1 = 0;
	double num2 = 0;
	 
    switch(cladata.opNum)  
    {
        case 1:		// plus+
        	if (cladata.flagnum1 == 1 || cladata.flagnum2 == 1)	// µÎ ¼ö ¸ğµÎ Á¤¼öÀÏ ¶§ 
        	{
        		cla_return.flagresult = 1;
        		
        		if ((cladata.inum1 + cladata.inum2) <= 2147483647 && (cladata.inum1 + cladata.inum2) >= -2147483648)
        		{
        			cla_return.iresult = cladata.inum1 + cladata.inum2;
				}
				else
				{
        			cla_return.opNum = 100;
        			return cla_return;
				}
				return cla_return;
			}
			
        	else
        	{
        		cla_return.flagresult = 2;
        		
        		if (cladata.flagnum1 == 1) 	// ÇÏ³ª´Â ¹«Á¶°Ç ½Ç¼öÀÓÀ¸·Î Ã¹ ¹øÂ°°¡ Á¤¼ö¸é µÎ ¹øÂ°´Â ½Ç¼ö 
        		{
					cla_return.dresult = cladata.inum1 + cladata.dnum1;
				}
												
        		else
        		{
        			cla_return.dresult += cladata.dnum1;
        			if (cladata.flagnum2 == 1)
        			{
						cla_return.dresult += cladata.inum1;						
					}
					
        			else
        			{
						cla_return.dresult += cladata.dnum2;
					}   				
				}
				return cla_return;
			} 

        case 2:		// Minus-
        	if (cladata.flagnum1 == 1 || cladata.flagnum2 == 1)	// µÎ ¼ö ¸ğµÎ Á¤¼öÀÏ ¶§ 
        	{
        		cla_return.flagresult = 1;
        		
        		if ((cladata.inum1 - cladata.inum2) <= 2147483647 && (cladata.inum1 - cladata.inum2) >= -2147483648)
        		{
        			cla_return.iresult = cladata.inum1 - cladata.inum2;
				}
				else
				{
        			cla_return.opNum = 100;
        			return cla_return;
				}
        		return cla_return;
			}
			
        	else
        	{
        		cla_return.flagresult = 2;
        		
        		if (cladata.flagnum1 == 1) 	// ÇÏ³ª´Â ¹«Á¶°Ç ½Ç¼öÀÓÀ¸·Î Ã¹ ¹øÂ°°¡ Á¤¼ö¸é µÎ ¹øÂ°´Â ½Ç¼ö 
        			cla_return.dresult = cladata.inum1 - cladata.dnum1;	
								
        		else
        		{
        			d_result += cladata.dnum1;
        			if (cladata.flagnum2 == 1)
        				cla_return.d_result -= cladata.inum1;
        			else
        				cla_return.d_result -= cladata.dnum2;
				}
				return cla_return;
			}

        case 3:		// Multiplication*
			if (cladata.flagnum1 == 1 || cladata.flagnum2 == 1)
			{
				cla_return.flagresult = 1;
				
				if ((cladata.inum1 * cladata.inum2) <= 2147483647 && (cladata.inum1 * cladata.inum2) >= -2147483648)
        		{
        			cla_return.iresult = cladata.inum1 * cladata.inum2;
				}
				else
				{
        			cla_return.opNum = 100;
        			return cla_return;
				}
				return cla_return;
			}
		
			else
			{
				cla_return.flagresult = 2;
				
				if (cladata.flagnum1 == 1)
				{
					num1 = cladata.inum1;
					num2 = cladata.dnum1;
				}
				else
				{
					num1 = cladata.dnum1;
					if (cladata.flagnum2 == 1)
						num2 = cladata.inum1;
					else
						num2 = cladata.dnum2;
				}
				
				while (1)
            	{
                	if ( fmod(num1, 1.0f) == 0 && fmod(num2, 1.0f) == 0)
                	    break;
                	num1 *= 10;
                	num2 *= 10;
                	n_point *= 100;
            	}
            	
            	cla_return.dresult = num1 * num2 / n_point;
            	return cla_return;
			}

        case 4:		//division/ 
        	if (cladata.flagnum1 == 1 || cladata.flagnum2 == 1)
			{
				cla_return.flagresult = 1;
				
				if ((cladata.inum1 / cladata.inum2) <= 2147483647 && (cladata.inum1 / cladata.inum2) >= -2147483648)
        		{
        			cla_return.iresult = cladata.inum1 / cladata.inum2;
				}
				else
				{
        			cla_return.opNum = 100;
        			return cla_return;
				}
				return cla_return;
			}
        
        	else
        	{
        		cla_return.flagresult = 2;
				
				if (cladata.flagnum1 == 1)
				{
					num1 = cladata.inum1;
					num2 = cladata.dnum1;
				}
				else
				{
					num1 = cladata.dnum1;
					if (cladata.flagnum2 == 1)
						num2 = cladata.inum1;
					else
						num2 = cladata.dnum2;
				}
				
				while (1)
            	{
                	if ( fmod(num1, 1.0f) == 0 && fmod(num2, 1.0f) == 0)
                	    break;
                	num1 *= 10;
                	num2 *= 10;
            	}
            	
            	cla_return.dresult = num1 / num2;
            	return cla_return
			}
    }
}

int main(int argc, char  *argv[]){
    while(1) {

        int s_sock; // listening port

        struct sockaddr_in s_addr;  // server ip addr
        struct sockaddr_in c_addr;  // clinet ip addr
        struct claData cladata;
        socklen_t c_addr_size;

        char msg[MAX_MSG_SIZE];
        int msg_len;
        int packet_len;
        double answer;


        if (argc != 2) {
            printf("Usage : %s <port>\n", argv[0]);
            exit(1);
        }

        s_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (s_sock == -1)
            error_handling("socket() error");

        memset(&s_addr, 0, sizeof(s_addr)); // socketaddr_in struct initialize
        s_addr.sin_family = AF_INET;
        s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // for server, localhost
        s_addr.sin_port = htons(atoi(argv[1])); // listen port#

        if (bind(s_sock, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) // bind port & ip to socket
            error_handling("bind() error");
        while (1) {   // server will not closes after client disconnect.
            while (1) {
                c_addr_size = sizeof(c_addr);
                memset(&cladata, 0, sizeof(cladata));
                //msg_len = recvfrom(s_sock, &cladata, sizeof(cladata), 0, (struct sockaddr*)&c_addr, &c_addr_size);
                packet_len = recvfrom(s_sock, &cladata, sizeof(cladata), 0, (struct sockaddr *) &c_addr, &c_addr_size);
                if (packet_len == -1 && strcmp(inet_ntoa(c_addr.sin_addr), "0.0.0.0")) {
                    error_handling("recvfrom() error");
                    continue;
                } else {
                    break;
                }
            }
            if (cladata.opNum == 6.0) {
                return 0;
            }
            answer = cal(cladata);
            //sleep(1);
            struct sockaddr_in address;
            memset(&cladata, 0, sizeof(cladata));
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = inet_addr("127.0.0.1");
            address.sin_port = htons(7905);
            cladata.opNum = 5;
            cladata.num1 = answer;
            cladata.num2 = answer;
            cladata.result = answer; // ê²°ê³¼ê°’ì— ì—°ì‚° ê²°ê³¼ ì €ì¥
            int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join, size, result = 0;
            if ((join = connect(client, (struct sockaddr *) &address, sizeof(address))) == -1)
                return 0;
            sendto(client, &cladata, sizeof(cladata), 0, (struct sockaddr *) &address, sizeof(address));


        }
    }
    return 0;
}

