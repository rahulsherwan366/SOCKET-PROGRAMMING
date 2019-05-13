//ASSIGNMENT-5 question-6 (udp) 

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
#define SERV_PORT 13

//maximum data transfer allowed
#define MAXLINE    4096                 

//=============================== str_cli modified ======================================
// This function has been modified which initailly has two parameters sockfd and *fp in
// daytimecli1.c program during lab. Now , since in this question we have to print port
// number and hostname using udp ,we are passing two more parameters which are *arg and port_number
// for doing the same and modifing fp as a character string.
//=======================================================================================
void
str_cli(char *fp, char *arg, int port_number)
{       
        //printing the day time
        printf("%s ",fp);

        //printing the hostname and handling the errors
        if(strcmp(arg,"fault")!=0)
        printf("The hostname is : %s \n",arg);
        else
        {
           printf("The hostname is not found please enter a valid IPA.\n");
           printf("(For localhost you can use 127.0.0.1 as an IPA) \n");
        }
        
        //printing the port number
        printf("The port number of the server is: %d \n",port_number);
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
	if (argc != 2)
		perror("usage: daytimecli1 <IPaddress>");
    
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
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr); // populating IPA part of servaddr after converting it to numeric form

    // declaring hello which will send a message hi to the server
    char hello[] = "hi"; 
 
    // For receiving the message from the server.
    char msg_received[MAXLINE];
   
    //sending hi to the server
	 sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
    
    //getting response from the server 
    n = recvfrom(sockfd, (char *)msg_received, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,&len); 

    //appending null character in the end
    msg_received[n] = '\0';            

    //getting host name
    struct hostent *host;

    //getting hostname in host variable which is a hostent type 
    host = gethostbyaddr(&servaddr.sin_addr,sizeof(servaddr.sin_addr),AF_INET);
    
    //handling error
    if (host) 
    { 
        // modified str_cli function call passing two extra parameter hostname and server port
	    str_cli(msg_received,host->h_name,SERV_PORT);
    }
    else
    {   
        str_cli(msg_received,"fault",SERV_PORT);
    }  

    //terminating
	exit(0);
}
// main ends here
