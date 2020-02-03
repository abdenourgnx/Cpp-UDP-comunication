#include <iostream>
#include <WS2tcpip.h>
#include <string>



 #pragma comment (lib , "ws2_32.lib")

using namespace std ;


int main(int argc , char* argv[])
{
	WSADATA data ;
	WORD version = MAKEWORD(2,2); 

	cout << "start" << endl ;

	int wsOk = WSAStartup(version , &data);

	if (wsOk != 0)
	{
		cout<< "Can't start  win sock" << wsOk ;
 		return 0;
 	}

 	sockaddr_in server ; 
 	server.sin_family = AF_INET;
 	server.sin_port = htons(54000);
 	server.sin_addr.S_un.S_addr  = inet_addr("127.0.0.1");
 	// inet_pton(AF_INET , "127.0.0.1" , &server.sin_addr);

 	SOCKET out = socket(AF_INET , SOCK_DGRAM  , 0) ;

 	string s(argv[1]);

 	while(true) {
 	    int sendOk = sendto( out , s.c_str() , s.size() +1 , 0 , (sockaddr*)&server , sizeof(server));

 		if (sendOk == SOCKET_ERROR)
 		{
 			cout << "Didn't send !" << WSAGetLastError() << endl ;
 		}
 	}
 	

 	closesocket(out) ;



 	WSACleanup();
}