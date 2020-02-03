#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define SERV_IP "172.20.11.111"

using namespace std ; 

int main(int argc, char const *argv[])
{

	struct sockaddr_in servSide ;
	int sd , rc ;
	int Socket ;

	




	if((sd = socket(AF_INET,SOCK_DGRAM,0)) <0 ){
		cout<< "failed getting socket"<< endl;
	}

 	servSide.sin_family = AF_INET;
 	servSide.sin_port = htons(PORT);
 	servSide.sin_addr.s_addr = inet_addr(SERV_IP) ;// htonl(INADDR_ANY); // ;


 	char servAddString[INET_ADDRSTRLEN];
	inet_ntop(servSide.sin_family, &servSide.sin_addr, servAddString, sizeof(servAddString));


 	cout << servAddString << endl ;


 	if(rc = bind( sd, (struct sockaddr *) &servSide, sizeof(servSide) ) <0 ){
 		cout<< "can't bind socket " << rc << endl ; 
 		return 0;
 	}






 	sockaddr_in client; 
 	socklen_t clientLen = sizeof(client);
   // memset(&client , clientLen);
    memset(&client, 0, clientLen);

    char buffer[1024];

    while(true){
 		
		string clientIp ;	

 		printf("waiting for client ...\n");

 		memset(&buffer, 0, sizeof buffer);
 		
 		int byteIn = recvfrom(sd , &buffer , 1024 , 0 , (struct sockaddr *)&client ,&clientLen );

 		if(byteIn <  0 ){
 			cout << "fail reciving from client" << endl; 
 			continue ;

 		}
 		
 		// inet_ntop( AF_INET, &client.sin_addr , clientIp ,256 );

 		// inet_pton(AF_INET , &clientIp , & client.sin_addr);

 		clientIp  = inet_ntoa(client.sin_addr);
 		cout << "Message recievd from " << clientIp << " : " << buffer << endl ; 
		 
		memset(&clientIp, 0, sizeof clientIp);
 		
 	}


	return 0;
}