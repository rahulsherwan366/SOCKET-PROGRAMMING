// ANSWERS OF THEORITICAL QUESTIONS OF QUESTION -3
// Observe what happens if you run the client before you run the server ?
// ANSWER: IT IS UNABLE TO CONNECT SINCE THE IPA PROVIDED IS LOCALHOST SO SINCE THE SERVER
//         IS NOT ON IT IS PRINTING "error in connect call" AS I HAVE WRITTEN BELOW FOR HANDLING 
//         CONNECT CALL.  

//CODE BELOW

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

//port using (hardcoding it)
#define SERV_PORT 3993

//maximum data transfer allowed
#define MAXLINE    4096                 

//str_cli modified of lab
void
str_cli(FILE *fp, int sockfd)
{
	char recvline[MAXLINE];
        
		if (read(sockfd, recvline, MAXLINE) == 0)
		{	perror("str_cli: server terminated prematurely");
            exit(0);
        }

        //printing hello, world which is the message it will always recieve by the server  
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
	if (argc != 4)
	{
        	printf("error in arguments \n");
            exit(0);
    }

    // socket call has SOCK_STREAM as a parameter which means it is a tcp client 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //removing garbage values in servaddr
	bzero(&servaddr, sizeof(servaddr));

    //populating servaddr 
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, "localhost", &servaddr.sin_addr); // populating IPA part of servaddr after converting it to numeric form
    
    
    int x;

    //connecting to the server
	x = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    //error handling
    if(x<0)
    {
        printf("error in connect call \n");
        exit(0);
    }

    //function to print the msg recieved by the server
    str_cli(stdin, sockfd);
    
    //closing the associated socket discripter
    close(sockfd);
}
// main ends here
// question - 3 (client) completed