#include <iostream>
#include <WS2tcpip.h>
#include <string>


 #pragma comment (lib , "ws2_32.lib")

using namespace std ;


int main()
{
	WSADATA data ;
	WORD version = MAKEWORD(2,2); 

	cout << "start" << endl ;

	int wsOk = WSAStartup(version , &data);

	if (wsOk != 0)
	{
		cout<< "Can't start  win sock" << wsOk ;
 	}

 	SOCKET in = socket(AF_INET, SOCK_DGRAM , 0);

 	
 	sockaddr_in serverHint ;
 	
 	
 	serverHint.sin_addr.S_un.S_addr = ADDR_ANY ;  // inet_addr("5.1.0.0") ;
 	serverHint.sin_family = AF_INET;
 	serverHint.sin_port = htons(54000);


 	cout << inet_ntoa(serverHint.sin_addr) << endl << ntohs(serverHint.sin_port) << endl ;


 	if( bind(in, (sockaddr*)&serverHint , sizeof(serverHint)) == SOCKET_ERROR )
 	{
 		cout << "Can't find socket ! " << WSAGetLastError() << endl;
 		return 0;
 	}

 	sockaddr_in client; 
 	int clientLen = sizeof(client);
    ZeroMemory(&client , clientLen);

 	char buffer[1024];

 	while(true){
 		

 		printf("waiting for client ...\n");

 		ZeroMemory(&buffer , 1024);
 		
 		int byteIn = recvfrom(in , buffer , 1024 , 0 , (sockaddr*)&client ,&clientLen );

 		if(byteIn == SOCKET_ERROR){
 			cout << "fail reciving from client" << WSAGetLastError() <<endl ; 
 			continue ;

 		}

 		string clientIp ;
 		

 		// inet_ntop( AF_INET, &client.sin_addr , clientIp ,256 );

 		// inet_pton(AF_INET , &clientIp , & client.sin_addr);

 		clientIp  = inet_ntoa(client.sin_addr);
 		cout << "Message recievd from " << clientIp << " : " << buffer << endl ; 
		 
		ZeroMemory( &clientIp , sizeof(clientIp) ); 
 		
 	}

 	closesocket(in);




	WSACleanup();
	return 0;
}