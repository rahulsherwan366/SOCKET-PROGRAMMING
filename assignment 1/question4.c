// Assignment - 5 (question - 4)

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

//alias name to constants 
#define SERV_PORT 13
#define MAXLINE    4096                 

//this function returns port number after converting it from network to host form. 
int get_port(struct sockaddr_in cliaddr)
{   
    //temp variable
    int ans;

    //convesion from network to host form
    ans = ntohs(cliaddr.sin_port);    

    //returning the port number
    return ans;
}

//this function returns IPA in ascii format 
char *get_IPA(struct sockaddr_in cliaddr,char temp[50])
{       
        //converting into numeric to ascii format
        strcpy(temp,inet_ntoa(cliaddr.sin_addr));
        
        //returning the IPA
        return temp;
}

//Main starts
int
main(int argc, char **argv) //arguments are optional
{   
    //variable initialization
	int			sockfd;
	struct sockaddr_in	servaddr,cliaddr;
    
    //assigning socket discripter to a tcp type socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //removing garbage values
	bzero(&servaddr, sizeof(servaddr));
	
    //populating servaddr
    servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
    
    //just connecting to any port 
	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    // iniatializing variables to new socket discripter
	int port_number; 
    socklen_t x = sizeof(cliaddr);

    //calling getsockname
	getsockname(sockfd, (struct sockaddr *) &cliaddr, &x);
	
    //some temp variables
    char temp[50],IPA[50];

    //calling get_port defined above.
    port_number = get_port(cliaddr);

    //calling get_IPA defined above.
    strcpy(IPA,get_IPA(cliaddr,temp));

    //printing the port and IP 
	printf("Port = %d\n", port_number);
	printf("IP = %s\n", IPA); 
    

	return 0;
}
//main ends
//question 4 solved.