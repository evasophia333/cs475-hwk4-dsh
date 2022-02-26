/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"


#define MAXBUF 256
#define HISTORY_LEN 100
char* historyLen[HISTORY_LEN];


int main(int argc, char **argv)
{
	char cmdline[MAXBUF]; // stores user input from commmand line
	messageOfDay();
	int exit = 0; 
    int elem = 0;
	while(exit==0){
        elem++;
		//continually print dsh>
		printf("\ndsh>");
		if(!fgets(cmdline,MAXBUF, stdin)){
            break;  //break if the input is too long
        }else{
            int runShell = shell(cmdline);
            addUserInput(cmdline);
            if(runShell==-1){
                exit = -1;
            }
        }   
	}

	return 0;
}
