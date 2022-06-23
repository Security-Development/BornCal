# BornCal

<<<<<<< HEAD
=======
```
Server : linux ubuntu 20.14
진행중....
```

### How To Use It?

```
---------------------------------
Variable Data Type
String ip
int port
---------------------------------
BonCalClientAPI API = new BonCalClientAPI(ip, port);
try{
   System.out.println("[+] Recive Message : "+API.GetReciveMessage()); // 서버에서 받은 메세지 
   API.SocketClose(); // 소켓 종료
}catch(Exception error) {
   error.printStackTrace();
}

```

### Client.c 결과
![image](https://user-images.githubusercontent.com/35417717/175282253-b3bda275-5940-4948-893b-e8cbbb6215fc.png)
>>>>>>> b2fba2f51a3493620c5d75dba1803ceba8abac69
