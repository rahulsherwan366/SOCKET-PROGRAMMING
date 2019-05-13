/*	ASSIGNMENT 5 (QUESTION 5)  */

//Header Required
#include    <stdio.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <netdb.h>
#include    <string.h>
#include    <arpa/inet.h>
#include    <stdlib.h>
#include    <netdb.h>


#define PORT 5549


/* ========================find_ip FUNCTION EXPLANATION====================================================================================
This function find_ip takes following arguments and returns a string which is basically an IPA in dotted notation:
      
      1) *host_name = It is a character to a pointer which takes a string ,over here in this code it taking machine name.
      2) hints = It is a object of struct addrinfo type , which is used as a parameter for calling getaddrinfo . We have populated
                 its ai_family with AF_INET which will allow IPv4 addresses searching only.
      3) *IPA = It is a pointer to the structure addrinfo which will finally contain the information about the machine name after executing getaddrinfo.
      4) converted_IPA = It is a temporary string which will just be returned after the execution of the function having an IPA in it.
===========================================================================================================================================
*/
char *find_ip(char *host_name , struct addrinfo hints, struct addrinfo *IPA, char converted_IPA[50])
{
      memset(&hints,0,sizeof(struct addrinfo));  // removing garbage values initially.
      hints.ai_family = AF_INET ; //Allow IPv4 
      int s; //checking the error term       

      /*==================GETADDRINFO CALL EXPLANATION===========================================
         1) getaddrinfo returns a value which is used to handle errors.
         2) However, this function is a call by reference function due to which the parameter IPA 
            gets populated even without returning it with information related to machine.
         3) NULL over here means it can take both SOCK_STREAM or SOCK_DGRAM.
      ============================================================================================
      */
      s = getaddrinfo(host_name, NULL, &hints, &IPA); 

      
      if(s!=0) 
      {
          printf("INVALID HOSTNAME ... Terminating process...\n"); // Handling Error.
          exit(0); // terminating the program.
      }
      
      //Converting IPA in ascii format and copying the converted IPA to converted_IPA variable.
      strcpy(converted_IPA,inet_ntoa(((struct sockaddr_in *) IPA->ai_addr)->sin_addr));   
      return converted_IPA;  // returning IPA in dotted notation.
}  
//find_ip function ends 


/* ========================find_host_name FUNCTION EXPLANATION==============================================================================
This function find_host_name takes following arguments and returns a string which is basically a machine name:
      
      1) *IP = It is a character to a pointer which takes a string ,over here in this code it taking machine's IPA.
      2) *temp = It is a temporary string which will just be returned after the execution of the function having a machine's name in it.
============================================================================================================================================
*/
char *find_host_name(char *IP,char temp[50])
{   
    //temp variable for handling errors
    int s;
    
    // creating socket address sa of struct sockaddr_in type
    struct sockaddr_in sa;
    char hbuf[NI_MAXHOST];
    
    // Removing initial garbage value.
    memset(&sa, 0, sizeof sa);

    //populating sa.sin_family 
    sa.sin_family = AF_INET;
    
    // converting from presentation to numeric
    inet_pton(AF_INET, IP, &sa.sin_addr);
    
    /*==================GETNAMEINFO CALL EXPLANATION===========================================
         1) getnameinfo returns a value which is used to handle errors.
         2) However, this function is a call by reference function due to which the parameter IPA 
            gets populated even without returning it with information related to machine.
         3) NULL over here means it can take both SOCK_STREAM or SOCK_DGRAM.
         4) The hbuf variable will finally contain the hostname after executing getnameinfo.
    ============================================================================================
    */
    s = getnameinfo((struct sockaddr*)&sa, sizeof(sa),hbuf, sizeof(hbuf),NULL, 0, NI_NAMEREQD);
   
    //error handling
    if(s!=0)
    {
        strcpy(hbuf,"unable to resolve try again");
    }
    
    strcpy(temp,hbuf);
    return temp;    // returning machine's name.
}
//find_host_name function ends 




//main function
int main()
{   
    //selecting options
    int ch;

do{ 
    //GUI options available
    printf("\n\nENTER YOUR CHOICE \n");
    printf("\t 1.) FOR CONVERTING MACHINE NAME TO IPA\n");
    printf("\t 2.) FOR CONVERTING IPA TO MACHINE NAME\n");
    printf("\t 3.) FOR EXITING\n");
    
    //INPUTING USER OPTION
    scanf("%d",&ch);

    

    if(ch==1)
    {
         // some temp variables
        int n,i=0;

        //input n for number of machine names.
        printf("\nEnter the number of hostname you want to enter : \n");
        scanf("%d",&n); 
   
        // variable declarations
         char host_name[n][100],IP_obtained[n][100],temp[50];
         struct addrinfo hints; 
        // result will contain the final IPA info.
        struct addrinfo *result; 
     
        printf("\nEnter the machine names:\n");
        for(i=0;i<n;i++)
        {   
            // inputing hostname/machine
            scanf("%s",host_name[i]); 

            // calling find_ip function and coping its returned value to host_name string array at ith location
            strcpy(IP_obtained[i],find_ip(host_name[i],hints,result,temp)); 
        }

        printf("The IPAs obtained are : \n");
        for(i=0;i<n;i++)
        {
            // printing the IPA obtained. 
            printf("%s ---> %s \n",host_name[i],IP_obtained[i]);

        }
    } 
    else if(ch==2)
    {
         // some temp variables
        int n,i=0;

        //input n for number of IPAs.
        printf("\nEnter the number of IPAs you want to enter : \n");
        scanf("%d",&n); 
   
        // variable declarations
         char host_name_obtained[n][100],IP[n][100],temp[50];
           
        printf("\nEnter the IPAs:\n");
        for(i=0;i<n;i++)
        {   
            // inputing hostname/machine
            scanf("%s",IP[i]); 

            // calling find_ip function and coping its returned     value to host_name string array at ith location
            strcpy(host_name_obtained[i],find_host_name(IP[i],temp)); 
        }

        printf("The host names obtained are : \n");
        for(i=0;i<n;i++)
        {
            // printing the IPA obtained. 
            printf("%s ---> %s \n",IP[i],host_name_obtained[i]);

        }        
    }  
    else if(ch==3)
    {   //if requested for exit.
        printf("exiting....\n");
    }
    else
    {   //If wrong choice entered.
        printf("YOU HAVE ENTERED A WRONG CHOICE.\n");
    }

}while(ch!=3);

return 0; 
}// main function ends here

//help:- from MAN page of getaddrinfo and getnameinfo

//question 5 solved.
