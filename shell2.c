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

		if(strcmp(scanned_input, "history") == 0)
		{
			if(argCount == 0)
			{
				printf("No command has been entered so far.\n");
				continue;
			}
			for(int i = 0; i < argCount; i++)
			{ 
				printf("%d\t%s\n", i + 1,past_com[i]);
			}
			continue;
		}

		if(scanned_input[0]=='!')
		{
			if(argCount == 0)
			{
			printf("Sorry, No arguments till now\n");
			continue;
			}
			if(scanned_input[1]=='!')
			{
				add_into_arr(past_com[0]);
				char s1[MAX_LINE];
				strcpy(s1,past_com[0]);
				tokenize(s1,args,&has_ampersand);
			}
			else
			{
				int n = scanned_input[1] - 48;
				if(n >= 11 && n <= 0)
				{
				printf("Not an Allowed operation\n");
					continue;
				}
				add_into_arr(past_com[n]);
				char s1[MAX_LINE];
				strcpy(s1,past_com[n]);
				tokenize(s1,args,&has_ampersand);
			}
		}
		else
		{	
			add_into_arr(scanned_input);
			tokenize(scanned_input,args,&has_ampersand);
		}
		pid_t child_pid;
		child_pid = fork();
		if(strcmp(*(args),"quit")==0)
			exit(0);
		if(child_pid==0)
		{
			execvp(args[0], args);
			fprintf (stderr,"an error occured in execvp\n");
			abort();
		}
		if(has_ampersand==true&&child_pid!=0)
			wait();
	}
}

