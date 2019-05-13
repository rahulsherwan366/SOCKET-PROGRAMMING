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


//The main function
int main(int argc,char **Host_name)
{   
	//variable initializations
	struct addrinfo hints , *result;
	int x;
    
	if (argc != 2)
	{
	printf("host_name required \n"); // Handling errors
	exit(0); // terminating the program
	}
    
	//zeroizing every data members of hints variable
	memset(&hints, 0, sizeof(struct addrinfo));

	//populating hints (help from man page of getaddrinfo())
	hints.ai_family = AF_INET;    /* Allow IPv4 only*/
    hints.ai_socktype = 0; /* socket address of any type can be returned */
    hints.ai_flags = AI_CANONNAME;    
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
	
	
	int len = strlen(Host_name[1]);
    
	//appending null character in the end
	Host_name[1][len] = '\0';

	//calling getaddrinfo() and error checking 
	if(x = getaddrinfo(Host_name[1],NULL, &hints, &result) != 0)
	{
		printf("error in getaddrinfo()\n");
		exit(0);
	}
    
	//variable for storing ip address
	char IP_addr[150];

	//converting the ip address to dotted notation and saving the result in IP_addr variable
	inet_ntop (result->ai_family, &((struct sockaddr_in *) result->ai_addr)->sin_addr, IP_addr, 150);
    
	//printing the final result obtained that is the IP address 
	printf("HOST : %s \n IP_ADDRESS : %s \n",Host_name[1],IP_addr); 
	return 0;
} 
// main funcion ends
//question-1 (completed) 
