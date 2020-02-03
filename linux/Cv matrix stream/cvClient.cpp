#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "opencv2/opencv.hpp"

#define PORT 8080
#define CLIENTIP "172.20.9.110"

using namespace cv;
typedef unsigned char byte;

using namespace std ; 

byte * matToBytes(Mat image);

int main(int argc, char const *argv[])
{	
	sockaddr_in client ;
	int sd ; 

	int send_data_len;
	char send_data[100];

	int bd = 1024 *10  ; 
	char s = 's' , f ='f' ;


	



	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	client.sin_addr.s_addr = inet_addr(CLIENTIP);

	if( (sd = socket(AF_INET , SOCK_DGRAM  , 0) ) < 0 ) {
		cout << "failed getting socket " << endl ;
	}




	VideoCapture cap(0);

	

	while(true){

		

		Mat resized ; 
		Mat frame;
        cap >> frame;

        resize(frame , resized, Size(frame.cols/3,frame.rows/3) );

        if( resized.empty() ) break; 
        imshow("this is you, smile! :)", resized);
        if( waitKey(10) == 27 ) break;

        int sizee = resized.total() * resized.elemSize();
	    byte* bytes = matToBytes(resized);
	    std::vector<uchar> v ;
	    imencode(".jpg" , resized , v);


	    cout << sizee << endl; 
	    cout << resized.cols << "hhh" << resized.rows << endl ; 

	    
	    sendto(sd , &s , 1 , 0 , (sockaddr*)&client , sizeof(client) ) ; 

	    for (int i = 0; i < sizee; i+=bd)
	    {
	    	sending[bd];

	    	for (int j = 0; j < bd; ++j)
	    	 {
	    	    sending[j] = bytes[i+j];
	    	 } 

	    	  send_data_len = sendto( sd  , &sending , bd , 0 , (sockaddr*)&client , sizeof(client));
	    }

	    

	   

	    if (send_data_len < 0 ) {
	  		cout<<"Client: sending error"<<endl;
	  		exit(1);
		}

		// if( frame.empty() ) break; 
  //         imshow("this is you, smile! :)", frame);
  //         if( waitKey(10) == 27 ) break; 


	    cout<<"Client: message sent "<<endl;



	}

	



	
	return 0;
}


byte * matToBytes(Mat image)
{
   int size = image.total() * image.elemSize();
   byte * bytes = new byte[size];  
   std::memcpy(bytes,image.data,size * sizeof(byte));
   return bytes ; 
}

