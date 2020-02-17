/* Name: Prakhar Rathi
ID:
Teammate name(s): Jaskaran Gujral 
*/

#include <stdio.h>
#include <unistd.h>
#include <stlib.h> 
#include <unistad.h> 

// CONSTANTS
#define MAX LINE 80 /* The maximum length command */ 

// Main Function 
int main(void)
{

char *args[MAX LINE/2 + 1]; /* command line arguments */
int should_run = 1; /* flag to determine when to exit program */ 
while (should_run) {

printf("osh>"); 
fflush(stdout);

/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) if command included &, parent will not invoke wait()
* (4) if command is quit, the shell should exit
* Explain your steps as comments in the code itself.
*/
return 0; 
}

// Fork fucntion 
int fork(int argc, char *argv[])
{
    // Printing the proces id 
    printf("I am a %d\n", (int)getpid()); 

    pid_t pid = fork(); 
    if (pid == 0)
    {
        printf("\nI am a child with pid %d", int getpid())
    } else if(pid> 0)
    {
        printf("\nI am a parent"); 
    } else
    {
        printf("\nFork Failed!"); 
    }
    print("\nFork returned: %d", int(pid))
    printf("\nI am a %d\n", (int)getpid())
    return 0; 
}