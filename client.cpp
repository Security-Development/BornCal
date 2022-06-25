#include <iostream>
#include <stdlib.h>
#include <set>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#pragma warning(disable: 4996)

using namespace std;

typedef struct Packet{
    short opcode;
    short data_len;
    char msg[50];
} Packet;

struct _clacData
{
	int opNum; // + - * ÷ result srvoff, 1 2 3 4 5 6
	double num1;  // 숫자1 입력
	double num2; // 숫자2 입력
	double result; // 결과 값 저장
};

struct _clacData Data;

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n',stderr);
    exit(1);
}

double getData(){

	int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join;
	struct sockaddr_in address;
	Packet packet;

	if( !client )
		return 0;

	memset(&address, 0, sizeof(address));
	memset(&packet, 0, sizeof(packet));

	int portnum = 7904;
	address.sin_port = htons(portnum);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");

	if( (join = connect(client, (struct sockaddr *) &address, sizeof(address))) == -1 )
			return 0;

	printf("[*] Connection Server !!\n");
	sendto(client, &Data, sizeof(Data), 0, (struct sockaddr *)&address, sizeof(address));
	printf("[+] Send To Data Data : 0x%x\n", Data);
	printf("[+] opNum : %d\n", Data.opNum);
	printf("[+] num1 : %lf\n", Data.num1);
	printf("[+] num2 : %lf\n", Data.num2);

	if (Data.opNum != 6) {
		//이 아래 문단은 서버로부터 들어오는 결과값을 받습니다. ... The paragraph below receives the resulting value from the server.
		struct sockaddr_in s_addr;  // server ip addr
		struct sockaddr_in c_addr;  // clinet ip addr
		int s_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
		socklen_t c_addr_size;
		memset(&s_addr, 0, sizeof(s_addr)); // socketaddr_in struct initialize
		s_addr.sin_family = AF_INET;
		s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // for server, localhost
		s_addr.sin_port=htons(7905); // listen port#
		if(bind(s_sock, (struct sockaddr*) &s_addr, sizeof(s_addr)) == -1)
			error_handling("bind() error");
		c_addr_size = sizeof(c_addr);
		memset(&Data, 0, sizeof(Data));
		int packet_len;
		packet_len = recvfrom(s_sock, &Data, sizeof(Data), 0, (struct sockaddr*)&c_addr, &c_addr_size);
		printf("packet_len : %d\n",packet_len);
		printf("result : %lf\n",Data.result);  // 결과 값 출력

		close(s_sock); // 소켓 해제
	}

	close(client); // 소켓 해제

	return 0;
}

void clear() {
	sleep(0.5);
	system("clear");
}

int clac() {

	while (1) {
		clear();

		cout << "사용할 연산자 번호를 입력 해주세요. + - * ÷ , 1 2 3 4 : ";
		cin >> Data.opNum;

		if ( !(cin.good() && (1 <= Data.opNum && Data.opNum <= 4)) ) {
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(1024, '\n');
			continue;
		}

		cout << "계산할 첫 번째 값을 입력 해주세요. : ";
		cin >> Data.num1;

		if ( !cin.good() ) {
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(1024, '\n');
			continue;
		}

		cout << "계산할 두 번째 값을 입력 해주세요. : ";
		cin >> Data.num2;

		if (!cin.good()) {
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(1024, '\n');
			continue;
		}

		getData();
		sleep(2);
		break;
	}
}

int main() {

	string str;
	set<string> commandSet{ "!calc","!cls" ,"!exit","!srvoff" };

	while (1) {
		clear();

		cout << "명령어를 입력해주세요. !calc !cls !exit !srvoff : ";
		cin >> str;

		if (cin.good() && str == "!calc")
		{	
			clac();
		}
		else if (cin.good() && str == "!cls")
		{
			clear();
		}
		else if (cin.good() && str == "!exit")
		{
			exit(0);
		}
		else if (cin.good() && str == "!srvoff")
		{
			int srvoff = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join;
			struct sockaddr_in off_addr;
			Packet packet;

			if( !srvoff )
				return 0;

			memset(&off_addr, 0, sizeof(off_addr));
			memset(&packet, 0, sizeof(packet));
			memset(&Data, 0, sizeof(Data));

			int portnum = 7904;
			off_addr.sin_port = htons(portnum);
			off_addr.sin_family = AF_INET;
			off_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			Data.opNum = 6;

			if( (join = connect(srvoff, (struct sockaddr *) &off_addr, sizeof(off_addr))) == -1 )
				return 0;
				
			sendto(srvoff, &Data, sizeof(Data), 0, (struct sockaddr *)&off_addr, sizeof(off_addr));
			close(srvoff);

			printf("서버가 종료되었습니다. \n");
			return 0;
		}
		else if (!cin.good() || commandSet.find(str) == commandSet.end())
		{
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(1024, '\n');
			continue;
		}
	}

}
