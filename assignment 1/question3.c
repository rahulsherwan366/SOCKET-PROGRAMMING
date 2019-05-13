// ASSIGNMENT-5 (question-3)

//Headers Required
#include <stdio.h>
#include <string.h>

// check_endianess function takes type casted hexadecimal value in its *check argument and 
// returns a string (i.e, returns *temp) populated with either "Little Endian" or "Big Endian" word.
char *check_endianess(char *check,char *temp)
{
     // checking if 66 is at 0 th index of check or not. (hex number is : 0x11225566)
     if(((int)check[0])==0x66) 
     { 
       printf("Value obtained at A[0] is : %.2x \n",check[0]);
       
       // populating string with Little Endian word
       strcpy(temp,"Little Endian"); 
     }
     else
     { 
       printf("value obtained at A[0] is : %.2x \n",check[0]);
       
       // populating string with Big Endian word
       strcpy(temp,"Big Endian"); 
     }
  
     // returning the string
     return temp; 
}
// check_endianess ends

//main function
int main()
{  
   // Considering any random hexadecimal value. For the time being it is let 0x11225566. 
   int hex_number = 0x11225566;

   //Initializing variables of character string type.
   char check[50],temp[10],result[50]; 

   //Informing User about default hexadecimal value.
   printf("I have considered a hexadecimal number to determine endianess which is : 0x11225566 \n");  
   
   //calling the function check_endianess and storing the returned by it value in result variable.
   strcpy(result,check_endianess((char *)&hex_number,temp));
   
   //Finally printing the output obtained.
   printf("Therefore, The type of our machine is : %s  \n",result);
   
   return 0;
}
// main ends