/*
Name: Jaskaran Gujral
SNU ID: 1810110091

Name: Prakhar Rathi
SNU ID: 1810110169
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/wait.h>

// CONSTANTS
#define MAX_LINE 80 // The maximum length command

// Array which will save the last 10 commands
char past_com[10][MAX_LINE];
int argCount = 0;

// Adding the commands to the past commands array
void add_into_arr(char *string) {
	
	for (int i = 9; i > 0; --i)
    	strcpy(past_com[i], past_com[i - 1]);
        
	strcpy(past_com[0], string);
	++argCount;
}

// Tokenization function: tokenizes the input stream and separates them on " "
bool tokenize(char *string, char **ret) {
	
	int i = 0;
	char *token[41];
	token[0] = strtok(string, " ");
	
	while(token[i] != NULL) {
		
		ret[i] = token[i];
		token[++i] = strtok(NULL, " ");
	}
	
	char arr1[10];
	strcpy(arr1, ret[i - 1]);
	token[i] = strtok(ret[i - 1], "&");
	
	if(strcmp(token[i], arr1) == 0) {
		
		ret[i] = NULL;
		return false;
	}
	
	else {
		
		ret[i - 1] = token[i];
		ret[i] = NULL;
		return true;
	}
}

// Displaying the last 10 commands 
void show_history() {
	
	if(argCount == 0)
		printf("No command has been entered so far.\n");
	
	else if(argCount < 11)
		for(int i = 0; i < argCount; ++i)
			printf("%d\t%s\n", argCount - i, past_com[i]);
	
	else
		for(int i = 0; i < 10; ++i)
			printf("%d\t%s\n", argCount - i, past_com[i]);
}

// Main Function 
int main(void){

	char *args[MAX_LINE/2 + 1]; // Command line arguments
	int should_run = 1; // Flag to determine when to exit program
	
	while (should_run) {

		char scanned_input[50];
		char *arg;

		printf("\nosh>"); 
		fflush(stdout);
		scanf("%[^\n]", scanned_input); // Command + Arguments input stream
        getchar();
        
		// Variable to check if there is an ampersand at the end
		bool has_ampersand;

		// Checking for the history command 
		if(strcmp(scanned_input, "history") == 0) {
			
			show_history(); 
			continue; 
		}

		// Executing the most recent commands
		if(scanned_input[0] == '!') {
			
			if(argCount == 0) {
				
				printf("No recent arguments to execute\n");
				continue;
			}

			if(scanned_input[1] == '!') { // !! Case : Execute most recent

				add_into_arr(past_com[0]);
				
				char s1[MAX_LINE];
				strcpy(s1,past_com[0]);
				has_ampersand = tokenize(s1, args);
				
				char com[MAX_LINE];
				strcpy(com,past_com[0]);
				has_ampersand = tokenize(com, args);
			}
			
			else {
				// Nth number for which the command has to be executed
				int n = scanned_input[1] - 48;
				
				if(n >= 11 || n <= 0) {
				printf("Only 10 commands can be displayed\n");
					continue;
				}

				add_into_arr(past_com[n]);
				
				char s1[MAX_LINE];
				strcpy(s1,past_com[n]);
				has_ampersand = tokenize(s1, args);
				
				char com[MAX_LINE];
				strcpy(com,past_com[n]);
				has_ampersand = tokenize(com, args);
			}
		}
		
		else {	
			add_into_arr(scanned_input);
			
			// Split the input into tokens and save them in an array
			has_ampersand = tokenize(scanned_input, args);
		}

		// Creating the child process id and forking the parent process
		pid_t child_pid;
		child_pid = fork();

		// If the quit statement is found 
		if(strcmp(*(args), "quit") == 0)			
			exit(0);
		
		if(strcmp(args[0], "cd") == 0) {
			char *loc_string = args[1];
			int found = chdir(loc_string);
			if(found < 0)
				printf("Location not found.\n");
			
			continue;
		}		
		
		if(child_pid == 0) {
			
			
			printf("\n");
			execvp(args[0], args);
			fprintf (stderr,"\nCommand not recognised.\n");
			abort();
		}

		// If an ampersand is not found
		if(has_ampersand == false)
			wait(NULL);
	}
}
