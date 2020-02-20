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
int argCount = 0; 
int stackPtr = 0; 
char past_com[10][MAX_LINE];

// Add the command to the past commands array
void add_into_array(char *string)
{
    if(stackPtr > 9)
    {
        stackPtr = 0; 
        strcpy(past_com[stackPtr], string); 
    }
    else
        strcpy(past_com[stackPtr], string);
}

// History function 
void showHistory()
{
    if(argCount == 0)
        printf("No command in the history"); 
    else
    {
        printf("These are the functions that you have used. \n"); 
        for(int i = 0; i <= stackPtr; i++)
            printf("%d\t %s\n", argCount - stackPtr + i, past_com[i]);
    }
    
}

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

int main(){
    int should_run = 1; /* flag to determine when to exit program*/
    int arg_no = 0; 
    while (should_run)
    { 
        char input[MAX_LINE]; 
        char *arg; 
        printf("osh>"); 
        fflush(stdout); 
        scanf("%[^\n]", input); 
        getchar(); 
        bool has_ampersand = 0;

        if(strcmp(input, "history") == 0)
        {
            showHistory(); 
        }
        if(input[0] == '!')
        {
            /* Do Something */ 
        } else
        {
            add_into_array(input); 
            tokenize(); 
        }

        pid_t child_pid; 
        child_pid = fork(); 
        if((strcmp(input, "quit")) == 0)
            exit(0); 
        if(child_pid == 0)
        {
            execvp(args[0], args); 
            printf("Error executing the command.\n"); 
            abort(); 
        }

        if(has_ampersand == true)
            wait(); 
    }

}


