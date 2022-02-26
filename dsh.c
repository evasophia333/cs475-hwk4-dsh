/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>
#include "builtins.h"

#define HISTORY_LEN 100
char historyLen[HISTORY_LEN];

/*
Prints the message of the day to the screen if .dsh_motd is found
*/
void messageOfDay(){
    //look for a file called .dsh_motd in the current user’s home directory
    const char *homeEnv = getenv("HOME");
	if(homeEnv){
	size_t size = strlen(homeEnv)+strlen(".dsh_motd");
	char *path = malloc(size);
	strcpy(path, homeEnv);
	strcpy(path, ".dsh_motd");
	if(access(path, F_OK)!=-1){ //go in if the file was found
		FILE *fptr = fopen(".dsh_motd","r");
        if(fptr==NULL){        //file not found then exit
            exit;  
        }else{
        char c = fgetc(fptr);
        while(c != EOF){
            printf("%c",c);
            c = fgetc(fptr);
        }
        fclose(fptr);
        }
	} //file not found do nothing
    }
}
/**
 * works the shell depedning on what the user wants
 * @returns specific numbers if the user needs to exit
 * @param user input
 **/
int shell(char* cmdline){
    cmdline [ strcspn(cmdline, "\r\n") ] = '\0'; //removes the new line at the end of input
    char *newArgs[2];
    if(cmdline[0]=='/'){
        //then look for the directory 
        if (access(cmdline, F_OK | X_OK) == 0) {
            int pid = fork();
            if(cmdline[strlen(cmdline)] != '&'){
             if(pid == 0) { //child
                newArgs[0] = cmdline;
                newArgs[1]= NULL;
                int status = execv(cmdline, newArgs);
                if(status !=0){
                    printf("ERROR!\n");
                }
            }else { //parent waits 
                wait(NULL);
            }
        }else{ //last char is &
            newArgs[0] = cmdline;
            newArgs[1]= NULL;
            int status = execv(cmdline, newArgs);
            if(status !=0){
                printf("ERROR!\n");
            }
        }
        }else {
            //if the path doesnt exist print an error
            printf("ERROR: %s not found!\n",cmdline); 
        }
    }else{
        char *token;
        token = strtok(cmdline, " "); //token stores the first word
        int command = builtInCommand(token);
        //check if the command is built in if so, run appropriate command
        if(command==1){
            //cd
            token = strtok(cmdline, " "); //second token (path)
            runCd(token);
        }else if(command==2){
            getPWD();
        }else if(command==3){
            //print recent commands
            printf("%s\n",historyLen);
            
            return 2;
        }else if(command==4){
            return -1; //to exit the dsh
        }
    }
    return 0;
}

/**
 * Determines if the command is built in or not
 */
int builtInCommand(char* command){
    if(strcmp(command,"cd")==0){
        return 1;
    }else if(strcmp(command, "pwd") == 0){
        return 2;
    }else if(strcmp(command, "history") == 0){
        return 3;
    }else if(strcmp(command, "exit") == 0){
        return 4;
    }else{
        printf("ERROR: %s not found!\n",command); 
        return -1;
    }
}
/**
 * Adds the user input into an array 
 */
void addUserInput(char* command){
    for(int i=0;i<HISTORY_LEN; i++){
        if(historyLen[i]==NULL){
            historyLen[i] = command;
        }
    }
}
/**
 * runs the CD function 
 */
void runCd(char *path){
    int ch = chdir(path);
    if(ch == -1){
        printf("ERROR: %s could not be found.\n", path);
    } else {
        char prt[MAXBUF];
        if(getcwd(prt, sizeof(prt))!=NULL){
            printf("%s\n", prt);
        }
    }
}
/**
 * gets the pwd for an inpuit
 */
void getPWD(){
    char arr[MAXBUF];
    char *directory = getcwd(arr, sizeof(arr));
    if(directory!=NULL){
        printf("%s\n", arr);
    }else{
        printf("ERROR: Unable to access location\n");
    }
}