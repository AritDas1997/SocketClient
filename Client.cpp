#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>


using namespace std ;

int a,b ;
char c[256],e[256] ;

void con()
{
        a = socket(AF_INET, SOCK_STREAM, 0) ;
        struct sockaddr_in mghaddress;
        mghaddress.sin_family = AF_INET ;
        mghaddress.sin_port = htons(51100) ;
        mghaddress.sin_addr.s_addr = INADDR_ANY ;
        int b ;
        b = connect(a, (struct sockaddr *)&mghaddress, sizeof(mghaddress));
        if(b<0){
        perror("ERROR while connecting") ;
        exit(1) ;
        }

}

void sendmsg()
{
        bzero(e,256) ;
        cout<<"\nEnter the message you want to send to server: " ;
        cin.getline(e,256) ;
        cin.ignore() ;
       // char e[256]="Hello Server it's client" ;
        send(a, e, sizeof(e), 0) ;

}

void receivemsg()
{
        bzero(c, 256) ;
        cout<<"\nMessage received from server: " ;
        recv(a, c, sizeof(c), 0) ;
        cout<<c ;

}

int main(){
        con() ;

        while(1)
        {
        receivemsg() ;
        sendmsg() ;
        }

return 0 ;
}
