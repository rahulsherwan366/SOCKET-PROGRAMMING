//	ASSIGNMENT 5 (QUESTION 2 )


//Header Required
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

#define PORT 3330


// Part 1 solved of question 2 
struct sockaddr_in first_function(char *IPA, struct sockaddr_in IPaddress)  //first function for converting dot notation of IPA to binary form
{	int x;
	
        // populating the address of struct sockaddr
	IPaddress.sin_family = AF_INET;		
        IPaddress.sin_port = htons(PORT);

	//calling inet_aton and populating IPaddress's sin_addr part with the IPA in binary form.
        x = inet_aton(IPA, &IPaddress.sin_addr);
	
	//Handling Errors.
	if(x!=0)
	{printf("inet_aton successfully executed \n");
	}	
	else 
	{printf("inet_aton unsuccessfull (please enter a valid IPA) \n");
 	exit(0);}

	//Returning IPaddress after populating it. 
	return IPaddress;
} 


/* Part 2 solved , of question 2.  Please note below that the argument IPaddress in following function is already populated structure with the help of function first defined above*/ 
void second_function(struct sockaddr_in IPaddress) //second function for reconverting into dot notation and printing it.
{	
	// variable declaration.
        char converted_IPA[30];

	//calling inet_ntoa to convert IPA in dotted notation in ascii format.
	strcpy(converted_IPA,inet_ntoa(IPaddress.sin_addr)); 

	// printing the desired output. 
	printf("The IPA obtained in dotted notation using inet_ntoa is: %s \n",converted_IPA); 
}


//The main function
int main(int argc,char **IPA)
{
	if (argc != 2)
	{perror("usage: tcpcli <IPaddress>"); // Handling errors
	exit(0); // terminating the program
	}

	struct sockaddr_in IPaddress;
		
	// first function call according to question for using inet_aton 
	IPaddress = first_function(IPA[1],IPaddress); 
	
	// second function call according to question for using inet_ntoa and printing the desired IPA in dotted notation.
	second_function(IPaddress); 
	return 0;
} // main funcion ends 


// question 2 solved.
