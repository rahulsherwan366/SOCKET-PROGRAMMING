//Headers Required
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<stdio.h>
#include	<errno.h>
#include 	<string.h>
#include 	<stdlib.h>
#include 	<arpa/inet.h>
#include 	<unistd.h>

//port using
#define SERV_PORT  9996

//maximum data transfer allowed
#define MAXLINE    4096                 

//=============================== str_cli modified ======================================
// This function has been modified which initailly has two parameters sockfd and *fp in
// daytimecli1.c program during lab. Now , it still has the same parameter but we are 
// using send call first so that the iterative server can respond the day time and echoed 
// message.
//=======================================================================================
void
str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
        fgets(sendline,MAXLINE,stdin);

        if (send(sockfd, sendline, sizeof(sendline),0) == 0)
			perror("str_cli: server terminated prematurely");

		if (read(sockfd, recvline, MAXLINE) == 0)
			perror("str_cli: server terminated prematurely");

        //printing the day time and echoed message
		fputs(recvline, stdout);
        
}
//str_cli ends here

//The main function
int
main(int argc, char **argv)
{   
    //Initializing variables
	int			sockfd;
	struct sockaddr_in	servaddr;

    //handling errors
	if (argc != 2)
		perror("usage: daytimecli1 <IPaddress>");
    
    // socket call has SOCK_STREAM as a parameter which means it is a tcp client 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //removing garbage values in servaddr
	bzero(&servaddr, sizeof(servaddr));

    //populating servaddr 
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr); // populating IPA part of servaddr after converting it to numeric form

    
	int x;

    //connecting to the server
    x = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    //error handling
    if(x<0)
    {
        printf("unable to connect \n");
        exit(0);
    }


    // modified str_cli function 
	str_cli(stdin, sockfd);

    //terminating
	exit(0);
}
// main ends here
//question -2 (client) completed