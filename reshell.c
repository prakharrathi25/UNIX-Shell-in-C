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
char past_com[10][MAX_LINE];

// Add the command to the past commands array
void add_into_array(char *string)
{
        for(int i = 9; i > 0; i--)
        {
            
        }
}
int main(){
    int should_run = 1; /* flag to determine when to exit program*/
    int arg_no = 0; 
    while (should_run)
    {
        int i = 0; 
        char input[MAX_LINE]; 
        char *arg; 
        printf("osh>"); 

        scanf("%[^\n]", input); 
        getchar(); 
        bool has_ampersand = 0;

        if(strcmp(input, "history") == 0)
        {
            /* Do something */ 
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
            printf("The function returned to the parent process.\n"); 
            abort(); 
        }

        if(has_ampersand == true && child_pid != 0)
            wait(); 
    }

}
