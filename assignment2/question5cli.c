//THEORITICAL QUESTION OF THIS CODE
// QUESTION:- Use appropriate command to find the state of the client, server processes. What are the states of the
//            processes ?
//ANSWER:- Please have a look at image 'question5(netstat).png'.
//         The command which i have run is :   netstat -a | grep 9955 | grep tcp
//         A) Server State : LISTEN
//            Client State : CLOSE
//         B) Server State : ESTABLISHED
//            Client State : ESTABLISHED
//         C) Server State : ESTABLISHED 
//            Client State : ESTABLISHED
//         D) Server State : 
//            Client state : TIME WAIT 
//         E) Server State : LISTEN
//            Client state : CLOSE
// YES, THERE IS A ZOMBIE PROCESS . CHILDPID OF SERVER IS IN ZOMBIE STATE.SINCE , ITS WORK HAS BEEN DONE SO PARENT SERVER
// NO LONGER REQUIRES IT AND THEREFORE, IT HAS BEEN SENT IN ZOMBIE STATE.
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
#define SERV_PORT  9955

//maximum data transfer allowed
#define MAXLINE    400              

//=============================== str_cli modified ==================================================
// Note that the function str_cli has been modified which was given to us in lab. Now, it 
// first send the message and the receives the message from the server and ouputs the echoed message 
// to the client side.
//===================================================================================================
void
str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE]="";
        
        // getting the input and storing it in sendline variable.
        fgets(sendline,MAXLINE,stdin);
        
        //sending the message to the server
        if (send(sockfd, sendline, sizeof(sendline),0) == 0)
			perror("str_cli: server terminated prematurely");
        
        //reading the message from the server
		if (read(sockfd, recvline, MAXLINE) == 0)
			perror("str_cli: server terminated prematurely");

        
        //printing the message received by the server
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
		perror("usage: <IPaddress>");
    
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
    
    for( ; ; )
    {
        // modified str_cli function 
	    str_cli(stdin, sockfd);
    }
    
}
// main ends here
//question -5 (client) completed