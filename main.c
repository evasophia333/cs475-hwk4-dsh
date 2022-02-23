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

int main(int argc, char **argv)
{
	char cmdline[MAXBUF]; // stores user input from commmand line
	printf("MOTD: %s\n", getenv("/home/ubuntu/cs475-hwk4-dsh/.dsh_motd"));
	messageOfDay();
	int exit = 0;
	while(exit==0){
		//continually print dsh>
		printf("dsh>");
		if(!fgets(cmdline,MAXBUF, stdin)){
            break;  //break if the input is too long
        }
        
	}

	return 0;
}
