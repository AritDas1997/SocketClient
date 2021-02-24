#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>



using namespace std ;

int a,b,c ;
char d[256] ;

void start()
{
	a = socket(AF_INET, SOCK_STREAM, 0) ;
	struct sockaddr_in mghaddress;
	mghaddress.sin_family = AF_INET ;
	mghaddress.sin_port = htons(52000) ;
	mghaddress.sin_addr.s_addr = INADDR_ANY ;
	int b ;
	b = bind(a, (struct sockaddr *)&mghaddress, sizeof(mghaddress));
	listen(a, 5) ;
       // int c ;
        c=accept(a, 0, 0) ;
}

void sendmsg()
{
//        char d[256] ;
	
	bzero(d,256) ;
	cout<<"\nEnter the message you want to send to client:" ;
	cin.getline(d,256) ;
//	cout<<sizeof(mghaddress) ;
      //  char d[256] = "Hello how are you i am fine here tata" ;

        send(c, d, sizeof(d), 0) ;
	
}

void receivemsg()
{     
        bzero(d,256) ;
        recv(c, d, sizeof(d), 0) ;
	cout<<"\nMessage received from client: "<<d ;
}

int main(){
        start() ;
	
     
        
  	sendmsg() ;
        receivemsg() ; 
	
        close(a) ;
       
        
      
	
        return 0 ;
        
      

}
 
