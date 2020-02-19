/* Name: Prakhar Rathi
ID:
Teammate name(s): Jaskaran Gujral
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// CONSTANTS
#define MAX_LINE 80 /* The maximum length command */
char *args[MAX_LINE/2 + 1]; /* command line arguments */

// Stack for saving the last 10 commands
int stackPtr = 0; 
char *past_com[10]; 

// Main Function
int main(void)
{

    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) {

        char scanned_input[50];
        printf("osh>");
        fflush(stdout);
        scanf("%[^\n", scanned_input);
        getchar();

        // Take an input and split it into tokens and save them in an array

        // Condition 4
        if(args[0] == "quit") {
            exit(0);
        }

        else {
            execvp(args[0], args);
        }

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
}

// Tokenization function: tokenizes the input stream and separates them on " "
// char *tokenize(char *string, bool ch)
// {
//     // Obtain the first token which is the command 
//     char *token = strtok(string, " "); 
//     int i = 0;
//     while(token != NULL) // parsing for all the other tokens
//     {
//         printf("%s\n", token); // printing each token
//         args[i] = token; 
//         i++; 

//         token = strtok(NULL, " ");   // EXPLANATION: @Jaskaran idk why this line is working. Please figure out.
//     }

//     // Print the command
//     printf("The command you entered is: %s", string[0]); 
    
//     // Return argument list 
//     return *args;
// }

// Tokenization function: tokenizes the input stream and separates them on " "
void tokenize(char *string) {

    // Obtain the first token which is the command 
    char *token;
    int i = 0;
    token = strtok (string," ");
   
    while (token != NULL) // parsing for all the other tokens
    {
        printf ("%s\n", token); // printing each token
        args[i++] = token;
        token = strtok (NULL, " ");
    }

    // Print the command
    printf("The command you entered is: %s", string[0]); 
}

// Display history
void showHistory()
{
    if(stackPtr < 10)
    {
        for(int i = stackPtr; i >= 0; i--)
        {
            printf("%d %s", i + 1, past_com[i]); 
        }
    }else
    {
        for(int i = 9; i >= 0; i--)
        {
            printf("%d %s", i + 1, past_com[i]); 
        }
    }
}

// Function to execute the most recent commands
void executeRecent(int n)
{
    if(n == 1)
    {
        char *current = past_com[stackPtr]; 
        char *curr_arg[50] = tokenize(current, 0); 
        execvp(curr_arg[0], curr_arg); 

    }else if(n > 1)
    {
        char *current = past_com[stackPtr - n]; 
        char *curr_arg[50] = tokenize(current, 0);
        execvp(curr_arg[0], curr_arg); 
    }
}

// Fork fucntion
// int fork(int argc, char *argv[])
// {
//     // Printing the proces id
//     printf("I am a %d\n", (int)getpid());

//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         printf("\nI am a child with pid %d", int getpid())
//     } else if(pid> 0)
//     {
//         printf("\nI am a parent");
//     } else
//     {
//         printf("\nFork Failed!");
//     }
//     print("\nFork returned: %d", int(pid))
//     printf("\nI am a %d\n", (int)getpid())
//     return 0;
// }

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

int getSize(char a[])
{
    int size = sizeof(a)/(sizeof(a[0])); 
    return size; 
}