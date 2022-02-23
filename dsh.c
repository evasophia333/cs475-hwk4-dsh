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
/*
Prints the message of the day to the screen if .dsh_motd is found
*/
void messageOfDay(){
    //look for a file called .dsh_motd in the current user’s home directory
    if( access( ".dsh_motd", F_OK ) != -1) //check if the file is found
    {
        if(getenv(".dsh_motd")!=NULL){
        //prints the message if there is one!
        printf("%s\n", getenv("HOME"));
    }
    }
    
}
/**
 * works the shell depedning on what the user wants
 **/
int shell(char* cmdline){
    char *newArgs[2];
    if(cmdline[0]=='/'){
        //then look for the directory 
        if (access(cmdline, F_OK | X_OK) == 0) {
            // file exists and is executable
            int pid = fork();
             if(pid == 0) { //child
                newArgs[0] = cmdline;
                newArgs[1]= NULL;
                int status = execv(cmdline, newArgs);
                if(status !=0){
                    printf("ERROR!");
                }
            }else { //parent waits 
                wait(NULL);
            }
        }else {
                    //if the path doesnt exist print an error

            printf("ERROR: %s not found!",cmdline); 
        }

    }else{
        //concatonate the word at white spaces and see if it is built in 
        //check if the command is built in if so, run appropriate command
        //if not split on $SPATH
    }
    return 0;
}