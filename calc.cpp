#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <set>

#pragma warning(disable: 4996)

using namespace std;

struct _clacData
{
	int opNum; // + - * ÷ result srvoff, 1 2 3 4 5 6
	double num1;  // 숫자1 입력
	double num2; // 숫자2 입력
};

void clear() {
	Sleep(500);
	system("cls");
}

int clac() {

	_clacData Data;

	while (1) {
		clear();

		Data = { 0,0,0 };

		cout << "사용할 연산자 번호를 입력 해주세요. + - * ÷ , 1 2 3 4 : ";
		cin >> Data.opNum;

		if ( !(cin.good() && (1 <= Data.opNum && Data.opNum <= 4)) ) {
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(INT_MAX, '\n');
			continue;
		}

		cout << "계산할 첫 번째 값을 입력 해주세요. : ";
		cin >> Data.num1;

		if ( !cin.good() ) {
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(INT_MAX, '\n');
			continue;
		}

		cout << "계산할 두 번째 값을 입력 해주세요. : ";
		cin >> Data.num2;

		if (!cin.good()) {
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(INT_MAX, '\n');
			continue;
		}

		break;
	}

	return 0;
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
			// srvoff
		}
		else if (!cin.good() || commandSet.find(str) == commandSet.end())
		{
			cout << "잘못된 값을 입력했습니다!! \n";
			cin.clear();  cin.ignore(INT_MAX, '\n');
			continue;
		}
	}

	

}
