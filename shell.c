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

// Tokenization function: tokenizes the input stream and separates them on " "
bool tokenize(char *string, char **ret) {

    // Obtain the first token which is the command 
    char *token;
    int i = 0;
    token = strtok (string," ");
   
    while (token != NULL) // parsing for all the other tokens
    {
        ret[i++] = token;
        token = strtok (NULL, " ");
    }

    --i;
    int j = strlen(ret[i]) - 1;
    if(ret[i][j] == '&')
        return true;
    else
        return false;
    
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
        char *current = past_com[0]; 
        char *curr_arg[50];
        tokenize(current, curr_arg); 
        execvp(curr_arg[0], curr_arg); 

    }else if(n > 1)
    {
        char *current = past_com[n - 1]; 
        char *curr_arg[50];
        tokenize(current, curr_arg);
        execvp(curr_arg[0], curr_arg); 
    }
}

// Function to add the command to the history list 
void add_to_history(char *string)
{
    if(stackPtr < 10)
        {
            past_com[stackPtr] = string; 
            stackPtr++; 
        }else if(stackPtr > 9)
        {
            stackPtr = 0; 
            past_com[stackPtr] = string;
            stackPtr++;  
        }

}

// Main Function
int main(void)
{

    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) {

        char scanned_input[50];
        printf("osh>");
        scanf("%[^\n]", scanned_input); // Command + Arguments input stream (Takes everything before new line char)
        getchar();

        // Checking for the history command
        if(strcmp(scanned_input, "history") == 0)
        {
            showHistory(); 

        } else if (scanned_input[0] == '!')
        {
            if(scanned_input[1] == '!') // Executing the most recent command
                executeRecent(1); 
            else
                executeRecent(scanned_input[1]); // Executing the nth most recent command 
        } else 
        {
             add_to_history(scanned_input); // Adds the command to the history commands array
        }
            

        // Variable to check if there is an ampersand at the end
        bool has_ampersand;

        // Split the input into tokens and save them in an array
        has_ampersand = tokenize(scanned_input, args); // Tokenize will return true if & is present

        // Creating the child process id and forking the parent process
        pid_t child_pid;
        child_pid = fork();

        // If quit statement is found
        if(strcmp(scanned_input, "quit") == 0)
        {
            should_run = 0; 
            exit(0);
        }
	
	if(child_pid == 0) 
        {
            execvp(args[0], args);
            fprintf (stderr,"Back in the parent process\n");
			abort();
        }

        // If an ampersand is found then 
        if(has_ampersand == true && child_pid != 0)
        {
            int stat;
            wait(); // Wait argument and status of the child?? 
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
