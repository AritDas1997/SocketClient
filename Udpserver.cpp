#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<fstream>

//#define PORT  63500
#define MAXLINE 1024


using namespace std ;

        struct comm_struct {
        int sequence;
        char array[11];
        char *name = array;
        char phone_no[13];
        double salary;
        };



        class Udpserver{

        string line ;
        char buff[40] ;
        struct sockaddr_in servaddr, cliaddr;
        int sockfd ;
        int len,p,i ;

        public :

        void connection(char *argv[]) ;
        void input() ;
        void quit() ;
        };



        void Udpserver::input(){

        ofstream od ;
        od.open("ABC.txt", ios::trunc) ;
        od.close() ;



        cout<<"\nEnter the number of packets:" ;
        cin>>p ;

        comm_struct A[p] ;

        for(i=0;i<p;i++){
        cout<<"\n Enter Sequence: " ;
        cin>>A[i].sequence ;
        cout<<"\n Enter salary:" ;
        cin>>A[i].salary ;
        cin.ignore() ;
        cout<<"\nEnter Name:" ;
        cin.getline(A[i].name,16) ;
        cin.ignore() ;
        cout<<"\nEnter Phone number:" ;
        cin.getline(A[i].phone_no,13) ;
        cin.ignore() ;
        }

od.open("ABC.txt", ios::app) ;


for(i=0;i<p;i++){
od<<A[i].sequence<<" "<<A[i].name<<" "<<A[i].phone_no<<" "<<A[i].salary<<endl ;
cout<<A[i].sequence<<" "<<A[i].name<<" "<<A[i].phone_no<<" "<<A[i].salary<<endl ;
}
od.close() ;


ifstream id ;
id.open("ABC.txt", ios::in) ;
 while(getline(id, line, '\n')) {
strcpy(buff, line.c_str());
sendto(sockfd, buff, strlen(buff),0, (struct sockaddr *)&cliaddr,len);
}

id.close() ;

}


        void Udpserver::connection(char *argv[]){
        char buffer[MAXLINE];
//    char hello[45]= "quit";

        string line ;

        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));


        servaddr.sin_family    = AF_INET; // IPv4
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(atoi(argv[1]));

        if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 ){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

        int  pi, n;

        len = sizeof(cliaddr);


        n = recvfrom(sockfd, buffer, MAXLINE,0, ( struct sockaddr *)&cliaddr,(socklen_t*)&len);
        buffer[n] = '\0';
        cout<<buffer;

   }

void Udpserver::quit(){

char hello[45]= "quit";

    sendto(sockfd, hello, strlen(hello),0, (struct sockaddr *)&cliaddr,len);
}


        int main(int argc, char *argv[]){
        if(argc < 2){
        cout<<"\nGive port number as input" ;
        exit(1) ;
        }

        Udpserver u ;
        u.connection(argv) ;
        u.input() ;
        u.quit() ;
        return 0;
        }
