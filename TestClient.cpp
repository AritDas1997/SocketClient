#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>

using namespace std ;

class Client
{
int a ;
int b ;
char c[256] ;
char e[256] ;

public:

Client(char *argv[]){
        a = socket(AF_INET, SOCK_STREAM, 0) ;
        struct sockaddr_in mghaddress;
        mghaddress.sin_family = AF_INET ;
        mghaddress.sin_port = htons(atoi(argv[2])) ;
//      mghaddress.sin_addr.s_addr = INADDR_ANY ;
        mghaddress.sin_addr.s_addr = inet_addr(argv[1]) ;
        int b ;
        b = connect(a, (struct sockaddr *)&mghaddress, sizeof(mghaddress));
        if(b<0){
        perror("ERROR while connecting") ;
        exit(1) ;
        }

}

void sendmsg(){
        bzero(e,256) ;
        cout<<"\nEnter the message you want to send to server: " ;
        cin.getline(e,256) ;
        cin.ignore() ;
        if(!bcmp(e, "quit", 4)){
        cout<<"Connection Terminated" ;
        exit(1) ;
        }

        send(a, e, sizeof(e), 0) ;

}

void receivemsg()
{
        bzero(c, 256) ;
        recv(a, c, sizeof(c), 0) ;
        if( (!bcmp(c, "quit", 4)) || (strlen(c)==0) ) {
        cout<<"Connection Terminated" ;
        exit(1) ;
        }
        cout<<"\nMessage received from server: "<<c ;

}

 };

        int main(int argc, char *argv[]){
        if(argc < 3){
        cout<<"Error.....Give ip and port number as argument" ;
        exit(1) ;
        }

        Client c(argv) ;

        while(1)
        {
       c.receivemsg() ;
       c.sendmsg() ;
        }

return 0 ;
}
