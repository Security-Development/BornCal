#include <stdio.h>
#include <string.h>
#include <windows.h>
//#include <regex>

struct clacData
{
    unsigned int opNum; // + - * ÷ , 1 2 3 4
    double num1;  // 숫자1 입력
    double num2; // 숫자2 입력
    
};

int main(){

//    regex reOP("/^[0-4]+$/");
//    regex reNum("^[-]?\d*(\.?\d*)$");
    
    clacData Data = {0,0,0};

	printf("사용할 연산자 번호를 입력 해주세요.: ");
    scanf("%d",&Data.opNum);
    
    printf("\n계산할 첫 번째 값을 입력 해주세요.: ");
    scanf("%1f",&Data.num1);
    
    printf("\n계산할 두 번째 값을 입력 해주세요.: ");
    scanf("%1f",&Data.num2);

}
