# BornCal
## Team member
* H310김본수: client  
* H310이승용: client  
* H310황성윤: readme  
* H3206박현경: readme  
* H3209양승철: server  
* H3219홍제만: server  

## Introduction

**Language/Development enviroments**
* C
* Ubuntu 18.04

**Program setting**

## 프로그램 동작

## 계산 명령 수행

## 오류 수정

## 프로그램 종료

## 프로그램 구조 분석
* 통신규약  
Client→Server  
  OP Code | 역할 | 데이터내용 
  ----- | :-----: | :-----:  
  1 | 실수 덧셈 + | 뎃셈 연산 요청  
  2 | 실수 뺄셈 - | 뺄셈 연산 요청  
  3 | 실수 곱셉 * | 곱셈 연산 요청
  4 | 실수 나눗셈 / | 나눗셈 연산 요청
  Server→Client  
  OP Coode | 역할 | 데이터내용
  ----- | :-----: | :-----:
  5 | 연산 결과 전송 | 결과값(실수)  
  6 | 서버 종료 |  
* Server
* Client
