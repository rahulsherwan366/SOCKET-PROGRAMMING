// ASSIGNMENT - 5 question 8 (udp daytime server program)

//Headers Required
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h> // For time()

// defining aliasses for constants
#define SERVPORT  9928
#define MAXLINE   4096
#define LISTENQ   28


// This function takes socket discriptors as arguments and a client socket address 
//and send the daytime to the client by writing in this discripter.
void
str_daytime(int listenfd,int sockfd,struct sockaddr_in cliaddr)
{
    //Variable decla
	time_t curr_time;
    char		line[MAXLINE];

    //initiallizing curr_time 
    curr_time = time(NULL);

    // writing daytime in line variable
    snprintf(line, sizeof(line), "%.24s\r\n", ctime(&curr_time));
    
    // n is for handling error
    int n; 

    //sending daytime to the client
    n = sendto(listenfd, line, 24, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    
    //handling error
    if (n < 0) 
      perror("ERROR in sendto");
}
//str_daytime ends

//main begins
int
main(int argc, char **argv)
{   
    printf("UDP DAY TIME server started (listening...)\n");
    //Inializing variables
    int				listenfd, connfd;
    struct sockaddr_in	cliaddr, servaddr;
    char line[MAXLINE];

    // This will follow tcp protocol as we can SOCK_STREAM below 
    if ((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket error"); 
		exit(1);
	}

    //zeroizing servaddr
    bzero(&servaddr, sizeof(servaddr));
	
    //populating servaddr
    servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERVPORT);

    //binding IPA and port number to the file descriptor
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
		perror("bind error");    

    // infinte loop since it is a server. 
    for( ; ; ) 
    {  
       int cliaddr_len = sizeof(cliaddr);
       // accepting the client in connfd descriptor
       connfd = recvfrom(listenfd, line, MAXLINE, 0, (struct sockaddr *) &cliaddr, &cliaddr_len);
       
        //handling error
        if (connfd < 0)
        perror("ERROR in recvfrom");
        
        //If server recieves some data from any client then it will print the following details about the client.
        printf("Received packet from %s \nFrom port number: %d\nMessage: %s\n\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), line);
        
        //calling str_daytime function
        str_daytime(listenfd,connfd,cliaddr);       
    }
    //closing listenfd discriptor
    close(listenfd);
}
//main ends
//help : - tcphelloechoserv.c
//question 8 solved.