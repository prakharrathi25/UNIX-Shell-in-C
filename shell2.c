/* Name: Prakhar Rathi
ID:
Teammate name(s): Jaskaran Gujral
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <sys/types.h>

// CONSTANTS
#define MAX_LINE 80 /* The maximum length command */

// Array for saving the last 10 commands
char past_com[10][MAX_LINE];
int argCount = 0;

// Adding the commands to the past commands array
void add_into_arr(char *string) {
	for (int i = 9; i > 0; i--)
    		strcpy(past_com[i], past_com[i-1]);
        
	strcpy(past_com[0], string);
        argCount++;
    	if(argCount>10)
	{
    		argCount=10;
    	}
}

void tokenize(char *s, char **args,bool *j)
{
	int i=0;
	char *ptr[41] ;
	ptr[0]= strtok(s," ");
	while(ptr[i]!=NULL)
	{
		*(args+i)=ptr[i];
		ptr[++i] = strtok(NULL," ");
	}
	char ptr1[10];
	strcpy(ptr1,*(args+i-1));
	ptr[i] = strtok(*(args+i-1),"&");
	if(strcmp(ptr[i],ptr1)==0)
	{
		*(args+i)=NULL;
		*j = true;
	}
	else
	{
		*(args+i-1)=ptr[i];
		*(args+i)=NULL;
		*j= false;
	}
}

// Displaying the last 10 commands 
show_history()
{
	if(argCount == 0)
	{
		printf("No command has been entered so far.\n");
		// continue;
	}else{
		for(int i = 0; i < argCount; i++)
		{ 
			printf("%d\t%s\n", argCount - i, past_com[i]);
		}
		// continue;
	}
}
// Main Function 
int main(void){

	char *args[MAX_LINE/2 + 1]; /* command line arguments */
	int should_run = 1; /* flag to determine when to exit program*/	
	while (should_run)
	{

		char scanned_input[50];
		char *arg;
		printf("osh>"); 
		fflush(stdout);
		scanf("%[^\n]", scanned_input); // Command + Arguments input stream
        	getchar();
        
		// Variable to check if there is an ampersand at the end
		bool has_ampersand;

		// Checking for the history command 
		if(strcmp(scanned_input, "history") == 0)
		{
			show_history(); 
			continue; 
		}

		// Executing the most recent commands
		if(scanned_input[0]=='!')
		{
			if(argCount == 0)
			{
			printf("No recent arguments to execute\n");
			continue;
			}
			if(scanned_input[1]=='!') // !! Case : Execute most recent 
			{
				add_into_arr(past_com[0]);
				char com[MAX_LINE];
				strcpy(com,past_com[0]);
				tokenize(com,args,&has_ampersand);
			}
			else
			{
				// Nth number for which the command has to be executes
				int n = scanned_input[1] - 48;
				if(n >= 11 || n <= 0)
				{
				printf("Only 10 commands can be displayed\n");
					continue;
				}
				add_into_arr(past_com[n]);
				char com[MAX_LINE];
				strcpy(com,past_com[n]);
				tokenize(com,args,&has_ampersand);
			}
		}
		else
		{	
			add_into_arr(scanned_input);

			// Split the input into tokens and save them in an array
			tokenize(scanned_input,args,&has_ampersand);
		}

		// Creating the child process id and forking the parent process
		pid_t child_pid;
		child_pid = fork();

		// If the quit statement is found 
		if(strcmp(*(args),"quit")==0)
			exit(0);

		if(child_pid==0)
		{
			execvp(args[0], args);
			fprintf (stderr,"an error occured in execvp\n");
			abort();
		}

		// If an ampersand is found 
		if(has_ampersand==true&&child_pid!=0)
			wait();
	}
}

