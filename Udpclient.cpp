#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//#define PORT 63500
#define MAXLINE 1024

using namespace std ;

        class Udpclient{
//int sockfd ;
//char buffer[MAXLINE];
//char hello[45] ;
        struct sockaddr_in servaddr;
        int len , n;


        public:
        int sockfd;
        char buffer[MAXLINE];
        void connecter(char *argv[]) ;
        void send() ;
        void receive() ;
        };


        void Udpclient::connecter(char *argv[]){
// len=sizeof(servaddr) ;

        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(atoi(argv[1]));
        servaddr.sin_addr.s_addr = INADDR_ANY;

        len=sizeof(servaddr) ;

        }




        void Udpclient::send(){
        char hello[45] = "Hii server from client" ;
        sendto(sockfd, hello, strlen(hello), 0 ,(struct sockaddr *)&servaddr,sizeof(servaddr));
        }


        void Udpclient::receive(){
        n = recvfrom(sockfd, buffer, MAXLINE,0, (struct sockaddr *)&servaddr,(socklen_t*)&len);
        buffer[n] = '\0';
        cout<<buffer<<"\n";
        n=0 ;
}


        int main(int argc , char *argv[]){

        if(argc < 3){
        cout<<"\nGive port number as input!!" ;
        exit(1) ;
        }

        Udpclient h ;

        h.connecter(argv) ;
        h.send() ;
   //  cout<<"Hello message sent to server\n";
        while(1){
//      Udpclient h ;
        h.receive() ;
        if(!bcmp(h.buffer, "quit", 4)){
        cout<<"Connection Terminated" ;
        exit(1) ;
        }
        }
        close(h.sockfd);
        return 0;
}
