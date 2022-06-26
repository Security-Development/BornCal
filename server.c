#include <stdio.h>

#include <math.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>

#include <limits.h>

const unsigned int header_len = sizeof(short) * 2;

typedef struct Packet {
  short opcode;
  short data_len;
  char msg[50];
}
Packet;

typedef struct _clacData {
  int opNum; // + - * / result srvoff, 1 2 3 4 5 6 

  int flagnum1; // int, double, none 1 2 3
  int flagnum2; // int, double, none 1 2 3

  int inum1; // i숫자1
  int inum2; // i숫자2

  double dnum1; // d숫자1
  double dnum2; // d숫자2

  int flagresult; // int, double, none 1 2 3 

  int iresult; // i결과 값
  double dresult; // d결과 값
}
_clacData;

#define MAX_MSG_SIZE 50

void error_handling(char * msg) {
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

int SafeAdd(int nLeftValue, int nRightValue) {
  if (nRightValue > 0) {
    if (nLeftValue > (INT_MAX - nRightValue))
      return 0;
    else
      return 1;
  } else if (nRightValue < 0) {
    if (nLeftValue < (INT_MIN - nRightValue))
      return 0;
    else
      return 1;
  }
}

int SafeSubtract(int nLeftValue, int nRightValue) {
  if (nRightValue > 0) {
    if (nLeftValue < INT_MAX + nRightValue)
      return 0;
    else
      return 1;
  } else if (nRightValue < 0) {
    if (nLeftValue > INT_MIN + nRightValue)
      return 0;
    else
      return 1;
  }
}

int SafeMultifly(int nLeftValue, int nRightValue) {
  if (nRightValue == 0 || nLeftValue == 0) {
    return 1;
  } else {
    if ((nLeftValue > 0 && nRightValue > 0) ||
      (nLeftValue < 0 && nRightValue < 0)) {
      if (abs(nRightValue) > (INT_MAX / abs(nLeftValue)))
        return 0;
      else
        return 1;
    } else {
      if (-abs(nRightValue) < (INT_MIN / abs(nLeftValue)))
        return 0;
      else
        return 1;
    }
  }
}

_clacData cal(_clacData cladata) { // calculate in accordance with claData
  int n_point = 1;
  _clacData cla_return = cladata;
  double num1 = 0;
  double num2 = 0;

  switch (cladata.opNum) {
  case 1: // plus+
    if (cladata.flagnum1 == 1 && cladata.flagnum2 == 1) 
    {
      cla_return.flagresult = 1;
      cla_return.iresult = cladata.inum1 + cladata.inum2;

      if (SafeAdd(cladata.inum1, cladata.inum2) == 0)
        cla_return.opNum = 100;

      return cla_return;
    } else {
      cla_return.flagresult = 2;

      if (cladata.flagnum1 == 1) 
      {
        cla_return.dresult = cladata.inum1 + cladata.dnum2;
      } else {
        cla_return.dresult = cladata.dnum1;
        if (cladata.flagnum2 == 1) {
          cla_return.dresult += cladata.inum2;
        } else {
          cla_return.dresult += cladata.dnum2;
        }
      }
      return cla_return;
    }

    case 2: // Minus-
      if (cladata.flagnum1 == 1 && cladata.flagnum2 == 1) 
      {
        cla_return.flagresult = 1;
        cla_return.iresult = cladata.inum1 - cladata.inum2;

        if (SafeSubtract(cladata.inum1, cladata.inum2) == 0)
          cla_return.opNum = 100;

        return cla_return;
      } else {
        cla_return.flagresult = 2;

        if (cladata.flagnum1 == 1) 
          cla_return.dresult = cladata.inum1 - cladata.dnum2;

        else {
          cla_return.dresult = cladata.dnum1;
          if (cladata.flagnum2 == 1)
            cla_return.dresult -= cladata.inum2;
          else
            cla_return.dresult -= cladata.dnum2;
        }
        return cla_return;
      }

      case 3: // Multiplication*
        if (cladata.flagnum1 == 1 && cladata.flagnum2 == 1) {
          cla_return.flagresult = 1;
          cla_return.iresult = cladata.inum1 * cladata.inum2;

          if (SafeMultifly(cladata.inum1, cladata.inum2) == 0)
            cla_return.opNum = 100;

          return cla_return;
        } else {
          cla_return.flagresult = 2;

          if (cladata.flagnum1 == 1) {
            num1 = cladata.inum1;
            num2 = cladata.dnum2;
          } else {
            num1 = cladata.dnum1;
            if (cladata.flagnum2 == 1)
              num2 = cladata.inum2;
            else
              num2 = cladata.dnum2;
          }

          while (1) {
            if (fmod(num1, 1.0f) == 0 && fmod(num2, 1.0f) == 0)
              break;
            num1 *= 10;
            num2 *= 10;
            n_point *= 100;
          }

          cla_return.dresult = num1 * num2 / n_point;
          return cla_return;
        }

        case 4: //division/ 
          if (cladata.flagnum1 == 1 && cladata.flagnum2 == 1) {
            cla_return.flagresult = 1;

            if ((cladata.inum1 / cladata.inum2) <= 2147483647 || (cladata.inum1 / cladata.inum2) >= -2147483648) {
              cla_return.iresult = cladata.inum1 / cladata.inum2;
            } else {
              cla_return.opNum = 100;
              return cla_return;
            }
            return cla_return;
          } else {
            cla_return.flagresult = 2;

            if (cladata.flagnum1 == 1) {
              num1 = cladata.inum1;
              num2 = cladata.dnum2;
            } else {
              num1 = cladata.dnum1;
              if (cladata.flagnum2 == 1)
                num2 = cladata.inum2;
              else
                num2 = cladata.dnum2;
            }

            while (1) {
              if (fmod(num1, 1.0f) == 0 && fmod(num2, 1.0f) == 0)
                break;
              num1 *= 10;
              num2 *= 10;
            }

            cla_return.dresult = num1 / num2;
            return cla_return;
          }
  }
}

int main(int argc, char * argv[]) {
  while (1) {

    int s_sock; // listening port

    struct sockaddr_in s_addr; // server ip addr
    struct sockaddr_in c_addr; // clinet ip addr
    struct _clacData _clacdata;
    socklen_t c_addr_size;

    char msg[MAX_MSG_SIZE];
    int msg_len;
    int packet_len;

    if (argc != 2) {
      printf("Usage : %s <port>\n", argv[0]);
      exit(1);
    }

    s_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (s_sock == -1)
      error_handling("socket() error");

    memset( & s_addr, 0, sizeof(s_addr)); // socketaddr_in struct initialize
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // for server, localhost
    s_addr.sin_port = htons(atoi(argv[1])); // listen port#

    if (bind(s_sock, (struct sockaddr * ) & s_addr, sizeof(s_addr)) == -1) // bind port & ip to socket
      error_handling("bind() error");
    while (1) { // server will not closes after client disconnect.
      while (1) {
        c_addr_size = sizeof(c_addr);
        //memset(&cladata, 0, sizeof(cladata));
        memset( & _clacdata, 0, sizeof(_clacdata));
        //msg_len = recvfrom(s_sock, &cladata, sizeof(cladata), 0, (struct sockaddr*)&c_addr, &c_addr_size);
        packet_len = recvfrom(s_sock, & _clacdata, sizeof(_clacdata), 0, (struct sockaddr * ) & c_addr, & c_addr_size);
        if (packet_len == -1 && strcmp(inet_ntoa(c_addr.sin_addr), "0.0.0.0")) {
          error_handling("recvfrom() error");
          continue;
        } else {
          break;
        }
      }
      if (_clacdata.opNum == 6.0) {
        return 0;
      }
      printf("packet_len : %d\n", packet_len);
      printf("_clacdata.opNum : %d\n", _clacdata.opNum);
      printf("_clacdata.flagnum1 : %d\n", _clacdata.flagnum1);
      printf("_clacdata.flagnum2 : %d\n", _clacdata.flagnum2);
      printf("_clacdata.inum1 : %d\n", _clacdata.inum1);
      printf("_clacdata.inum2 : %d\n", _clacdata.inum2);
      printf("_clacdata.dnum1 : %1f\n", _clacdata.dnum1);
      printf("_clacdata.dnum2 : %1f\n", _clacdata.dnum2);

      _clacData answer;
      answer = cal(_clacdata);

      printf("answer.iresult : %d\n", answer.iresult);
      printf("answer.dresult : %lf\n", answer.dresult);
      printf("answer.opNum : %d\n", answer.opNum);
  
      memset( & _clacdata, 0, sizeof(_clacdata));
      
      struct sockaddr_in address;
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = inet_addr("127.0.0.1");
      address.sin_port = htons(7905);

      int client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP), join, size, result = 0;
      if ((join = connect(client, (struct sockaddr * ) & address, sizeof(address))) == -1)
        return 0;
      sendto(client, & answer, sizeof(answer), 0, (struct sockaddr * ) & address, sizeof(address));
      memset( & answer, 0, sizeof(answer));
      
      printf("-----------------------------\n");

    }
  }
  return 0;
}
