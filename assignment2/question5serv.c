// ASSIGNMENT - 5 ,question 9 (tcp concurrent daytime server program)

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
#define SERVPORT  9955
#define MAXLINE         4096
#define LISTENQ         28


char
str_echo(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];

	if ( (n = read(sockfd, line, MAXLINE)) == 0)
		return 'n';		/* connection closed by other end */
    else{
            write(sockfd, line, strlen(line));
            return 'y';
    }
}
//str_echo ends

//main begins
int
main(int argc, char **argv)
{   
    printf("TCP (CONCURRENT) server started (listening...)\n");
    
    //Inializing variables
    int				listenfd, connfd;
    pid_t				childpid;
    socklen_t			clilen;
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
       clilen = sizeof(cliaddr);
       // accepting the client in connfd descriptor
       if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) == -1) 
 			perror("accept error");
       
       //If server recieves some data from any client then it will print the following details about the client.
        printf("Received packet from %s \nFrom port number: %d\n\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

        if ( (childpid = fork()) == 0) {  /* child process */
	 		close(listenfd);	/* close listening socket */
		for( ; ;)
    {   char r;
        r = str_echo(connfd);	/* process the request */
        if(r!='y')
        {
          exit(0);
        }
    }
    		
		}
		close(connfd);	     /* parent closes connected socket */
    }
}
//main ends
//question 9 solved.