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

// Take an input and split it into tokens and save them in an array 


/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) if command included &, parent will not invoke wait()
* (4) if command is quit, the shell should exit
* Explain your steps as comments in the code itself.
*/

// Condition 4


return 0; 
}

// Tokenization function: tokenizes the input stream and separates them on " "
char *tokenize(char string[MAX LINE/2 + 1])
{
    // Obtain the first token which is the command 
    char *token = strtok(string, " "); 
    int i = 0; 
    while(token != NULL)
    {
        printf("%s\n", token); //printing each 
    }
    // Print the command
    printf("The command you entered is: %s", string[0]); 
    
    // Return argument list 
    return args; 
}

// Execute vp command
int execvp(char *command, char *params[])
{

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

// Function to print Current Directory. 
void printCurrDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); //get current working directory
    printf("\nDir: %s", cwd); 
} 

// Help Function in the Shell 
void openHelp() 
{ 
    puts("\n***WELCOME TO OUR SHELL HELP***"
        "\nCreated by @ Jaskaran and Prakhar"
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>quit"
        "\ncat"
        "\n>improper space handling"); 
  
    return; 
} 