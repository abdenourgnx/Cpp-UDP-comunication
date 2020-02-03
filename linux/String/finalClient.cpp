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
#define CLIENTIP "172.20.11.111"

using namespace std ; 

int main(int argc, char const *argv[])
{	
	sockaddr_in client ;
	int sd ; 

	int send_data_len;
	char send_data[100];




	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	client.sin_addr.s_addr = inet_addr(CLIENTIP);

	if( (sd = socket(AF_INET , SOCK_DGRAM  , 0) ) < 0 ) {
		cout << "failed getting socket " << endl ;
	}

	while(true){

		cout<<"Client: input message to send"<<endl;
	    cin>>send_data;



	    send_data_len = sendto( sd  , &send_data, sizeof(send_data) +1 , 0 , (sockaddr*)&client , sizeof(client));

	    if (send_data_len < 0 ) {
	  		cout<<"Client: sending error"<< send_data_len<<endl;
	  		exit(1);
		}


	    cout<<"Client: message sent "<<endl;



	}

	



	
	return 0;
}
