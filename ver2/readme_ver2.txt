초기의 ver(sion)2는 송수신 함수를 전부 지닌 Client가 Client에게 메세지를 전달하는데에 Server가 끼여있는 형태의 카톡방같은 기능을 수행하는 코드를 만들기  위해 만들어졌습니다.
하지만 계획이 바뀌어 지금은 자체제작 패킷 구조체를 적용할 수 있게 만드는 것을 목적으로 사용중입니다.
메인 코드는 u_cl.c 와 u_sv.c 가 있으며, v2cli.c 와 v2ser.c 는 더이상 개발되고있지 않습니다.

Early ver(sion)2 was created to create code that performs functions such as a kakaotalk room in which a client with all of the transmit and receive functions is trapped in the form of a server to deliver messages to the client.
However, the plan has changed and is now being used to make self-made packet structures applicable.
The main codes are u_cl.c and u_sv.c, and v2cli.c and v2ser.c are no longer being developed.
