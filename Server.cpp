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


using namespace std ;

int a,b,c ;
char d[256] ;
struct timeval stop, start  ;

void start_connect()
{
        a = socket(AF_INET, SOCK_STREAM, 0) ;
        struct sockaddr_in mghaddress;
        mghaddress.sin_family = AF_INET ;
        mghaddress.sin_port = htons(55555) ;
        mghaddress.sin_addr.s_addr = INADDR_ANY ;
        int b ;
        b = bind(a, (struct sockaddr *)&mghaddress, sizeof(mghaddress));

        if(b<0){
        perror("ERROR on binding\n") ;
        exit(1) ;
        }
        listen(a, 5) ;
        c=accept(a, 0, 0) ;
}

void sendmsg()
{

        bzero(d,256) ;
        cout<<"\nEnter the message you want to send to client:" ;
        cin.getline(d,256) ;

        send(c, d, sizeof(d), 0) ;

}

void receivemsg()
{
        bzero(d,256) ;
        recv(c, d, sizeof(d), 0) ;
        cout<<"\nMessage received from client: "<<d ;
}


int main(){
        start_connect() ;

        while(1)
        {
        gettimeofday(&start, NULL);
        sendmsg() ;
        receivemsg() ;

       if(!bcmp(d, "quit", 4)){
        cout<<"\nConnection Terminated" ;
        break ;
        }





        gettimeofday(&stop, NULL);

//        cout<<"\n"<<stop.tv_sec - start.tv_sec ;


        if(  (stop.tv_sec - start.tv_sec) > 14 ){
        cout<<"\nClient responded lately.....so terminating" ;
        break ;
        }

 }


//      cout<<"\n"<< stop.tv_sec - start.tv_sec ;
        close(a) ;
        return 0 ;



     }

