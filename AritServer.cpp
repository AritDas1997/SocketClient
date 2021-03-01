#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<fstream>


using namespace std ;

//int a;
ofstream os ;

class Server{

char d[256] ;
int b ;
int c;
int opt ;


public:

int a ;

Server(char *argv[])
{
        opt=1 ;
        os.open("logit.txt", ios::trunc);
        os.close() ;
        a = socket(AF_INET, SOCK_STREAM, 0) ;
        struct sockaddr_in mghaddress;

        if(setsockopt(a, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
        perror("setsockopt error");
        exit(1);
        }
        mghaddress.sin_family = AF_INET ;
        mghaddress.sin_port = htons(atoi(argv[2])) ;
//      mghaddress.sin_addr.s_addr = INADDR_ANY ;
        mghaddress.sin_addr.s_addr = inet_addr(argv[1]) ;
        int addrlen = sizeof(mghaddress) ;
        int b ;
        b = bind(a, (struct sockaddr *)&mghaddress, sizeof(mghaddress));

        if(b<0){
        perror("ERROR on binding\n") ;
        exit(1) ;
        }
        listen(a, 5) ;
//        c=accept(a, 0, 0) ;
        c=accept(a, (struct sockaddr *)&mghaddress,(socklen_t*)&addrlen) ;
        if(c < 0){
        perror("ERROR on accept\n") ;
        exit(1) ;
        }
}

void sendmsg()
{
        bzero(d,256) ;
        os.open("logit.txt", ios::app) ;
        cout<<"\nEnter the message you want to send to client:" ;
        cin.getline(d,256) ;
        os << "Server: " ;
        os << d  << endl;
        os.close() ;
        if(!bcmp(d, "quit", 4)){
        cout<<"Connection Terminated" ;
        exit(1) ;
        }


        send(c, d, sizeof(d), 0) ;

}

void receivemsg()
{
        os.open("logit.txt", ios::app);
        bzero(d,256) ;
        recv(c, d, sizeof(d), 0) ;
        if( (!bcmp(d, "quit", 4)) || (strlen(d)==0) ) {


        cout<<"\nConnection terminated" ;
        exit(1) ;
        }
        os << "Client: " ;
        os << d << endl ;
        os.close() ;

        cout<<"\nMessage received from client: "<<d ;
}

};

int main(int argc, char *argv[]){

        if(argc < 3 ){
        cout<<"Error.....Give port number as argument" ;
        exit(1) ;
        }

        struct timeval stop, start  ;


        Server s(argv) ;
        while(1)
        {
        gettimeofday(&start, NULL);
        s.sendmsg() ;
        s.receivemsg() ;





        gettimeofday(&stop, NULL);

        cout<<"\n"<<"Time Taken: "<<stop.tv_sec - start.tv_sec ;


        if(  (stop.tv_sec - start.tv_sec) > 30 ){
        cout<<"\nClient responded lately.....so terminating" ;
        break ;
        }

 }


        close(s.a) ;
        return 0 ;



     }
