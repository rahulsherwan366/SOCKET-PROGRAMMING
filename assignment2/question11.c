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

//maximum data transfer allowed
#define MAXLINE    4096                 

//str_cli modified of lab
void
str_cli(FILE *fp, int sockfd, char *filename,char *machine_name)
{
	char sendline[MAXLINE],recvline[MAXLINE];

    // http request packet format appending in sendline variable
    strcpy(sendline,"GET /");
    strcat(sendline,filename);
    strcat(sendline," HTTP/1.x\r\nHost: ");
    strcat(sendline,machine_name);
    strcat(sendline,"\r\n\r\n Connection: keep-alive\r\n\r\n Keep-Alive: 300\r\n");

    //sending the message to the server
    if (send(sockfd, sendline, sizeof(sendline),0) == 0)
	{	perror("str_cli: server terminated prematurely");
        exit(0);
    }

    // receiving the response package of http from the server
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
    ///////////////////////////////////////////////
    // PART 1 FINDING THE IPA (QUESTION1 CODE)   //
    ///////////////////////////////////////////////


    //variable initializations
	struct addrinfo hints , *result;
	int y;
    
	//handling errors
	if (argc != 5)
	{
        	printf("error in arguments \n");
            exit(0);
    }
    
	//zeroizing every data members of hints variable
	memset(&hints, 0, sizeof(struct addrinfo));

	//populating hints (help from man page of getaddrinfo())
	hints.ai_family = AF_INET;    /* Allow IPv4 only*/
    hints.ai_socktype = SOCK_STREAM; /* socket address of any type can be returned */
    hints.ai_flags = AI_CANONNAME;    
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
	
	
	int len = strlen(argv[1]);
    
	//appending null character in the end
	argv[1][len] = '\0';

	//calling getaddrinfo() and error checking 
	if(y = getaddrinfo(argv[1],NULL, &hints, &result) != 0)
	{
		printf("error in getaddrinfo()\n");
		exit(0);
	}
    
	//variable for storing ip address
	char IP_addr[150];

	//converting the ip address to dotted notation and saving the result in IP_addr variable
	inet_ntop (result->ai_family, &((struct sockaddr_in *) result->ai_addr)->sin_addr, IP_addr, 150);

    ////////////////////////////////////////////////////////////////////
    // PART2 - CONNECTING TO THE SERVER AND OBTAINING DESIRED MESSAGE //
    ////////////////////////////////////////////////////////////////////


    //Initializing variables
	int			sockfd;
	struct sockaddr_in	servaddr;   

    // socket call has SOCK_STREAM as a parameter which means it is a tcp client 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //removing garbage values in servaddr
	bzero(&servaddr, sizeof(servaddr));
    
    int z;
    z = atoi(argv[2]);

    //populating servaddr 
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(z);
	inet_pton(AF_INET, IP_addr, &servaddr.sin_addr); // populating IPA part of servaddr after converting it to numeric form
    
    
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
    str_cli(stdin, sockfd, argv[4],argv[1]);
    
    //closing the associated socket discripter
    close(sockfd);
}
// main ends here
// question -11 ( HTTP client) completed