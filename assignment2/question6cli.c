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
#define SERV_PORT  9900

//maximum data transfer allowed
#define MAXLINE    80              

//=============================== str_cli modified ======================================
// Note that the function str_cli has been modified which was given to us in lab. Now, it
// has a return type of char * earlier it was just void. We are doing this because when client 
// says goodbye then server will respond with the message "terminate connection" which we need to 
// compare in order to terminat infinite for loop which is running in the main . That's why , we 
// are changing the str_cli return type from void to char * type.
//=======================================================================================
char
*str_cli(FILE *fp, int sockfd, char *server_message)
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

        if(strcmp(recvline,"terminate connection")!=0)
        {
            //printing the message received by the server
		    fputs(recvline, stdout);    
        }
        strcpy(server_message,recvline);
        // returning the received message from the server
        return server_message;
        
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

    char server_message[MAXLINE];
    

    for( ; ; )
    {
        // modified str_cli function 
	    strcpy(server_message,str_cli(stdin, sockfd,server_message));

        if(strcmp(server_message,"terminate connection")==0)
        {
            //terminating
	        exit(0);
        }
    }
    
}
// main ends here
//question -6 (client) completed