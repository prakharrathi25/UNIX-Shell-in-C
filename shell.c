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
        scanf("%[^\n", scanned_input); // Command + Arguments input stream 
        getchar();

        // Variable to check if there is an ampersand at the end
        bool has_ampersand; 

        // Split the input into tokens and save them in an array
        tokenize(scanned_input, &has_ampersand); // @jaskaran Second argument is a place holder. add whatever is required

        // Creating the child process id and forking the parent process
        pid_t child_pid; 
        child_pid = fork(); 

        // If quit statement is found
        if(args[0] == "quit") 
        {
            exit(0);
        }

        // Checking for the history feature 
        if(args[0] == "history")
        {
            showHistory(); 

        } else if (args[0][0] == '!')
        {
            if(args[0][1] == '!') // Executing the most recent command
                executeRecent(1); 
            else
                executeRecent(args[0][1]); // Executing the nth most recent command 
        } else if(child_pid == 0) 
        {
            execvp(args[0], args);
            fprintf (stderr,"an error occured in execvp\n");
			abort();
        }

        // If an ampersand is found then 
        if(has_ampersand == true && child_pid != 0)
        {
            wait(); 
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
void tokenize(char *string, char **ret) {

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
        char *curr_arg[50];
        tokenize(current, curr_arg); 
        execvp(curr_arg[0], curr_arg); 

    }else if(n > 1)
    {
        char *current = past_com[stackPtr - n]; 
        char *curr_arg[50];
        tokenize(current, curr_arg);
        execvp(curr_arg[0], curr_arg); 
    }
}


int getSize(char *a)
{
    int size = sizeof(a)/(sizeof(a[0])); 
    return size; 
}