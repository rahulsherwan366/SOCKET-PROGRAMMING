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
#define SERV_PORT 3993

//maximum data transfer allowed
#define MAXLINE    4096                 

//function to print the message of received from the udp server
void
str_cli(char *fp)
{       
        //printing the message received from the server
        printf("%s ",fp);
}
//str_cli ends here

//The main function
int
main(int argc, char **argv)
{   
    //Initializing variables
	int			sockfd , n, len;
	struct sockaddr_in	servaddr;

    //handling errors
	if (argc != 4)
	{	perror("error in arguments ");
        exit(0);
    }
    
    // socket call has SOCK_DGRAM as a parameter which means it is a udp client 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    //removing garbage values in servaddr
	bzero(&servaddr, sizeof(servaddr));

    //populating servaddr 
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, "localh", &servaddr.sin_addr); // populating IPA part of servaddr after converting it to numeric form

    // For receiving the message from the server.
    char msg_received[MAXLINE];
   
    //sending hi to the server
	 sendto(sockfd, (const char *)argv[3], strlen(argv[3]), MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
    
    //getting response from the server 
    n = recvfrom(sockfd, (char *)msg_received, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,&len); 

    //appending null character in the end
    msg_received[n] = '\0';            

    // modified str_cli function call passing two extra parameter hostname and server port
	str_cli(msg_received);
    
    //closing associated socket discripter
    close(sockfd);
}
// main ends here
// question - 4 (client) completed