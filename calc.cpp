#include <stdio.h>
#include <string.h>
#include <windows.h>
//#include <regex>

struct clacData
{
    unsigned int opNum; // + - * �� , 1 2 3 4
    double num1;  // ����1 �Է�
    double num2; // ����2 �Է�
    
};

int main(){

//    regex reOP("/^[0-4]+$/");
//    regex reNum("^[-]?\d*(\.?\d*)$");
    
    clacData Data = {0,0,0};

	printf("����� ������ ��ȣ�� �Է� ���ּ���.: ");
    scanf("%d",&Data.opNum);
    
    printf("\n����� ù ��° ���� �Է� ���ּ���.: ");
    scanf("%1f",&Data.num1);
    
    printf("\n����� �� ��° ���� �Է� ���ּ���.: ");
    scanf("%1f",&Data.num2);

}
