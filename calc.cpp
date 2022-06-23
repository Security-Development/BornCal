#include <iostream>
#pragma warning(disable: 4996)

using namespace std;

struct _clacData
{
    int opNum; // + - * ÷ , 1 2 3 4
    double num1;  // 숫자1 입력
    double num2; // 숫자2 입력

};

int clac() {

    _clacData Data = {0,0,0};

    while (true) {

        cout << "사용할 연산자 번호를 입력 해주세요. : ";
        cin >> Data.opNum;
        if (cin.good()) {

            cout << "계산할 첫 번째 값을 입력 해주세요. : ";
            cin >> Data.num1;
            if (cin.good()) {

                cout << "계산할 두 번째 값을 입력 해주세요. : ";
                cin >> Data.num2;
                if (cin.good()) {

                    // 여기서 데이터 넘기면 됩니다.
                }
                else
                    cout << "잘못된 값을 입력했습니다!! \n";
                    cin.clear();  cin.ignore(INT_MAX, '\n');
                    continue;
            }
            else
                cout << "잘못된 값을 입력했습니다!! \n";
                cin.clear();  cin.ignore(INT_MAX, '\n');
                continue;   
        }
        else
            cout << "잘못된 값을 입력했습니다!! \n";
            cin.clear();  cin.ignore(INT_MAX, '\n');
            continue;
        
        break;
    }

    printf("%d %1f %1f", Data.opNum, Data.num1, Data.num2);
}

int main() {

    clac();
}
