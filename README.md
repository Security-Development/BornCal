# BornCal

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
