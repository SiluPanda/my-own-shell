#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

char **tokenize(char *line)
{
    char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for(i =0; i < strlen(line); i++){

        char readChar = line[i];

        if (readChar == ' ' || readChar == '\n' || readChar == '\t') {
            token[tokenIndex] = '\0';
            if (tokenIndex != 0){
                tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
                strcpy(tokens[tokenNo++], token);
                tokenIndex = 0; 
            }
        } 
        else {
            token[tokenIndex++] = readChar;
        }
    }
 
    free(token);
    tokens[tokenNo] = NULL ;
    return tokens;
}

void sig_int_handler(int signum){
    ;
}

//This function executes the commands with buildin execvp 
void exec_tokens(char **tokens){
    pid_t pid = fork();
    if(pid != 0){
        wait(NULL);
    }
    else if(pid == 0){
        int k = execvp(tokens[0], tokens);
        if(k == -1){
            printf("Command not found ");
        }
    }
}

void valid_tokens(char **tokens){
    //if nothing given
    if(tokens[0] == NULL){
        return;
    }
    //validating exit command
    if(strcmp("exit", tokens[0]) == 0){
        if(tokens[1] != NULL){
            printf("Wrong format, exit takes 0 arguments\n");
        }
        else{
            exit(0);
        }
    }

    if(strcmp(tokens[0], "cd") == 0) {
            if(tokens[1] == NULL)
            {
                printf("NO arguments given\n");
                return;
            }
            else if(tokens[2] != NULL) {
                printf("cd does not mora than one arguments \n");
                return;
            }

            //changing directory
            int f = chdir(tokens[1]);
            if(f == -1)
                printf("Directory not found\n");
            return;
        }

        
        exec_tokens(tokens);
        

}


int main(void)
{
    char  line[MAX_INPUT_SIZE];            
    char  **tokens;              
    int i;

    while (1) {           
       
        printf("Turtle>");     
        bzero(line, MAX_INPUT_SIZE);
        gets(line);           
        //printf("Got command %s\n", line);
        line[strlen(line)] = '\n'; //terminate with new line
        tokens = tokenize(line);
   
        //do whatever you want with the commands, here we just print them

        for(i=0;tokens[i]!=NULL;i++){
            //printf("found token %s\n", tokens[i]);
        }
       valid_tokens(tokens);
        // Freeing the allocated memory	
        for(i=0;tokens[i]!=NULL;i++){
            free(tokens[i]);
        }
        free(tokens);
    }

    return 0;
     

}

                