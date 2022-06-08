//송신자
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int retval;// 데이터 보내기( 구조체 크기를 먼저 보낸다. )
int len = sizeof( player );

retval = send( sock, (char *)&len, sizeof( int ), 0 );
if ( retval == SOCKET_ERROR ) {
err_display( "send()" );
exit( 1 );
}// 데이터 보내기( 구조체 데이터를 보낸다. )

retval = send( sock, (char*)&player, sizeof( Player_Socket ), 0 );
if ( retval == SOCKET_ERROR ) {err_display( "send()" );
exit( 1 );
}