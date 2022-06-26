# 🧮 BornCal    
> 사칙연산(+, -, ×, ÷)을 포함하는 연산식을 입력받아 처리하는 UDP 프로그램
## Team member
* H3107김본수: Client  
* H3112이승용: Client  
* H3119황성윤: Readme  
* H3206박현경: Readme  
* H3209양승철: Server   
* H3219홍제만: Server  

## Introduction

**Language/Development enviroments**
* C/C++
* Ubuntu 18.04  
  
**Program setting**  
* Server  
```
gcc -o server server.cpp -fno-stack-protector -no-pie -lm
```  
* Client  
```  
g++ -o client client.cpp -fno-stack-protector -no-pie -lm
```  
## 프로그램 실행    
* ./server 7904 → ./client  
## 계산 명령 수행
* 명령어   
  **!calc**   
  피연산자와 연산자를 서버에 보낸다.    
  **!cls**  
  터미널창의 출력 결과 새로고침 한다.  
  **!exit**  
  프로그램을 종료시킨다.    
  **!srvoff**  
  서버를 종료시킨다.    
  
* **case 1**   
30 + 20  
  ![정수 정수 덧셈](https://user-images.githubusercontent.com/74813313/175808469-ba05c4f9-c540-411e-bbde-b7715ae75641.png)   
* **case 2**   
31 - 14.5  
  ![정수 실수 뺄셈](https://user-images.githubusercontent.com/74813313/175808514-fa1433f6-9174-4484-bde6-f86c735f5220.png)     
* **case 3**     
32.323 × 20  
  ![실수 정수 곱셈](https://user-images.githubusercontent.com/74813313/175808558-2a84b2ab-9d49-4fc2-a109-164789ee15ad.png)   
* **case 4**   
32.123 ÷ 12.4  
  ![실수 실수 나눗셈](https://user-images.githubusercontent.com/74813313/175808571-28a50c1e-0f3f-4753-9d37-094b2ae53dcd.png)  
* **case 5**  
33333333 × 22222222  
  ![오버플로우](https://user-images.githubusercontent.com/74813313/175809960-a4822ef0-27fb-4d0e-8bdb-71571285221f.png)    

## 오류 수정

## 프로그램 종료

## 프로그램 구조 분석
* 통신규약  
  Flag | 내용    
  ----- | :-----:    
  1 | 정수형 자료형    
  2 | 실수형 자료형     
  3 | 해당 없음   
 
  **Client→Server**    
  OP Code | 역할 | 데이터내용 
  ----- | :-----: | :-----:  
  1 | 실수 덧셈 + | 뎃셈 연산 요청  
  2 | 실수 뺄셈 - | 뺄셈 연산 요청  
  3 | 실수 곱셉 × | 곱셈 연산 요청
  4 | 실수 나눗셈 ÷ | 나눗셈 연산 요청
  
  **Server→Client**  
  OP Coode | 역할 | 데이터내용
  ----- | :-----: | :-----:
  5 | 연산 결과 전송 | 연산 결과 값    
  6 | 서버 종료 |     
  100 | 연산 에러 전송 | 오버플로우, 언더플로우 발생     
