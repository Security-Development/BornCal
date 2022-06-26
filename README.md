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
* **!calc**   
계산기에 넣을 연산자와, 데이터를 입력받을 수 있는 calc() 함수를 동작시킬 수 있다.    
* **!cls**  
시스템의 clear 커맨드를 동작시켜 커멘드창의 출력 결과를 모두 지운다.  
* **!exit**  
프로그램을 종료시키는 exit() 함수를 실행시킨다.  
* **!srvoff**  
server 측에 opcode 6를 보내 서버를 종료시킨다.  
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
