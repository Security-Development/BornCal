#include <iostream>

#include <stdlib.h>

#include <set>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>

#include <limits.h>

#include <float.h>

#pragma warning(disable: 4996)

using namespace std;

typedef struct Packet {
  short opcode;
  short data_len;
  char msg[50];
}
Packet;

struct _clacData {
  int opNum; // + - * ÷ result srvoff ofuf , 1 2 3 4 5 6 100

  int flagnum1; // int, double, none 1 2 3
  int flagnum2; // int, double, none 1 2 3

  int inum1; // int 숫자1
  int inum2; // int 숫자2

  double dnum1; // double 숫자1
  double dnum2; // double 숫자2

  int flagresult; // int, double, none 1 2 3

  int iresult; // int 결과 값
  double dresult; // double 결과 값
};

struct _clacData cladata = {
  0,
  3,
  3,
  0,
  0,
  0,
  0,
  3,
  0,
  0
}; // flag none 지정, 나머지는 0으로 초기화

void error_handling(char * msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

double getData() {

  int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join;
  struct sockaddr_in address;
  Packet packet;

  if (!client)
    return 0;

  memset( & address, 0, sizeof(address));
  memset( & packet, 0, sizeof(packet));

  int portnum = 7904;
  address.sin_port = htons(portnum);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");

  if ((join = connect(client, (struct sockaddr * ) & address, sizeof(address))) == -1)
    return 0;

  printf("[*] Connection Server !!\n");
  sendto(client, & cladata, sizeof(cladata), 0, (struct sockaddr * ) & address, sizeof(address));
  printf("[+] Send To Data Data : 0x%x\n", cladata);
  printf("[+] opNum : %d\n", cladata.opNum);

  if (cladata.flagnum1 == 1) // int
  {
    printf("[+] num1 : %d\n", cladata.inum1);
  } else if (cladata.flagnum1 == 2) { // double
    printf("[+] num1 : %1f\n", cladata.dnum1);
  }

  if (cladata.flagnum2 == 1) // int
  {
    printf("[+] num2 : %d\n", cladata.inum2);
  } else if (cladata.flagnum2 == 2) { // double
    printf("[+] num2 : %1f\n", cladata.dnum2);
  }

  if (cladata.opNum != 6) {
    //이 아래 문단은 서버로부터 들어오는 결과값을 받습니다.
    struct sockaddr_in s_addr; // server ip addr
    struct sockaddr_in c_addr; // clinet ip addr
    int s_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    socklen_t c_addr_size;
    memset( & s_addr, 0, sizeof(s_addr)); // socketaddr_in struct initialize
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // for server, localhost
    s_addr.sin_port = htons(7905); // listen port#
    if (bind(s_sock, (struct sockaddr * ) & s_addr, sizeof(s_addr)) == -1)
      error_handling("bind() error");
    c_addr_size = sizeof(c_addr);
    memset( & cladata, 0, sizeof(cladata));
    int packet_len;
    packet_len = recvfrom(s_sock, & cladata, sizeof(cladata), 0, (struct sockaddr * ) & c_addr, & c_addr_size);

    printf("packet_len : %d\n", packet_len);

    if (cladata.opNum != 100) {
      if (cladata.flagresult == 1) { // int
        printf("result : %d\n", cladata.iresult); // int 결과 값 출력
      } else if (cladata.flagresult == 2) { // double
        printf("result : %1f\n", cladata.dresult); // int 결과 값 출력
      }
    } else if (cladata.opNum == 100) {
      printf("연산 과정에서 오버플로우나 언더플로우가 발생했습니다!! \n");
    }

    close(s_sock); // 소켓 해제
  }

  close(client); // 소켓 해제
  memset( & cladata, 0, sizeof(cladata));

  return 0;
}
void clear() {
  sleep(1);
  system("clear");
}

int clac() {

  while (1) {
    clear();

    cout << "사용할 연산자 번호를 입력 해주세요. + - * ÷ , 1 2 3 4 : ";
    cin >> cladata.opNum;

    if (!(cin.good() && (1 <= cladata.opNum && cladata.opNum <= 4))) {
      cout << "잘못된 값을 입력했습니다!! \n";
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    double typecheck; // 정수, 실수 판별

    cout << "계산할 첫 번째 값을 입력 해주세요. : ";
    cin >> typecheck;

    if (!cin.good()) {
      cout << "잘못된 값을 입력했습니다!! \n";
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }
    if (typecheck >= INT_MAX) {
      printf("오버플로우가 발생했습니다!! \n");
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    if (typecheck < INT_MIN) {
      printf("언더플로우가 발생했습니다!! \n");
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    if (typecheck - (int) typecheck == 0) { // 정수

      cladata.flagnum1 = 1;
      cladata.inum1 = (int) typecheck;
    } else if (typecheck - (int) typecheck != 0) { // 실수
      cladata.flagnum1 = 2;
      cladata.dnum1 = typecheck;
    }

    cout << "계산할 두 번째 값을 입력 해주세요. : ";
    cin >> typecheck;

    if (!cin.good()) {
      cout << "잘못된 값을 입력했습니다!! \n";
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    } else if (cladata.opNum == 4 && typecheck == 0) {
      printf("0 으로 나눌 수 없습니다!! \n");
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    if (typecheck >= INT_MAX) {
      printf("오버플로우가 발생했습니다!! \n");
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    if (typecheck < INT_MIN) {
      printf("언더플로우가 발생했습니다!! \n");
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }

    if (typecheck - (int) typecheck == 0) { // 정수
      cladata.flagnum2 = 1;
      cladata.inum2 = (int) typecheck;
    } else if (typecheck - (int) typecheck != 0) { // 실수
      cladata.flagnum2 = 2;
      cladata.dnum2 = typecheck;
    }

    getData();
    sleep(1.5);
    break;
  }
}

int main() {

  string str;
  set < string > commandSet {
    "!calc",
    "!cls",
    "!exit",
    "!srvoff"
  };

  while (1) {
    clear();

    cout << "명령어를 입력해주세요. !calc !cls !exit !srvoff : ";
    cin >> str;

    if (cin.good() && str == "!calc") {
      clac();
    } else if (cin.good() && str == "!cls") {
      clear();
    } else if (cin.good() && str == "!exit") {
      printf("클라이언트가 종료되었습니다. \n");
      exit(0);
    } else if (cin.good() && str == "!srvoff") {
      int srvoff = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join;
      struct sockaddr_in off_addr;
      Packet packet;

      if (!srvoff)
        return 0;

      memset( & off_addr, 0, sizeof(off_addr));
      memset( & packet, 0, sizeof(packet));
      memset( & cladata, 0, sizeof(cladata));

      int portnum = 7904;
      off_addr.sin_port = htons(portnum);
      off_addr.sin_family = AF_INET;
      off_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
      cladata.opNum = 6; // opNum 6 지정

      if ((join = connect(srvoff, (struct sockaddr * ) & off_addr, sizeof(off_addr))) == -1)
        return 0;

      sendto(srvoff, & cladata, sizeof(cladata), 0, (struct sockaddr * ) & off_addr, sizeof(off_addr));
      close(srvoff);

      printf("서버가 종료되었습니다. \n");
      return 0;
    } else if (!cin.good() || commandSet.find(str) == commandSet.end()) {
      cout << "잘못된 값을 입력했습니다!! \n";
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }
  }
}
