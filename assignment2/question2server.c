// Note : I AM PRINTING THE PORT NUMBER AND IPA OF THE CLIENT AND ALSO ITS MESSAGE ON THE SERVER SIDE EVEN THOUGH IT IS NOT ASKED
// IN THE QUESTION JUST TO LET US KNOW THAT SOME CLIENT CONNECTED TO THE SERVER

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
#define SERVPORT  9996
#define MAXLINE         4096
#define LISTENQ         28


// This function takes socket discriptor as an argument and send the daytime and echoed message ("hello client appended") to the 
//client by writing in this discripter.
void
str_daytime(int sockfd)
{
    //Variable declaration
	time_t curr_time;
    char		line[MAXLINE],line1[MAXLINE];

    //initiallizing curr_time 
    curr_time = time(NULL);

    //receiving the message from the client
    recv(sockfd,line1,sizeof(line),0);

    //printing the message recieved on the server side
    printf("MESSAGE RECIEVED : %s",line1);

    //getting the daytime
    snprintf(line, sizeof(line), "%.24s\r\n", ctime(&curr_time));
    
    //concatinating the hello client with the message recieved by the client
    strcat(line1,"Hello Client \n");

    //concatinating the daytime with message recieved
    strcat(line1,line);

    //writing it on the associated socket discriptor
    write(sockfd, line1, strlen(line1));
}
//str_daytime ends

//main begins
int
main(int argc, char **argv)
{   
    printf("TCP (ITERATIVE) DAY TIME server started (listening...)\n");
    //Inializing variables
    int				listenfd, connfd;
    struct sockaddr_in	cliaddr, servaddr;

    // This will follow tcp protocol as we can SOCK_STREAM below 
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
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

    //initializing listen mode
	if ((listen(listenfd, LISTENQ)) == -1)
		perror("listen error");

    // infinte loop since it is a server. 
    for( ; ; ) 
    {  
       int cli_len = sizeof(cliaddr);
       // accepting the client in connfd descriptor
       connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &cli_len);
       
       //If server recieves some data from any client then it will print the following details about the client.
        printf("Received packet from %s \nFrom port number: %d\n\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

       //calling str_daytime function
       str_daytime(connfd);

       //closing the client descriptor
       close(connfd);
    }
}
//main ends
//question 2 (iterative server) completed.