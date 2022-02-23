#include <stdio.h>
#include <stdlib.h>
/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define HISTORY_LEN 100



#ifndef DSH_H
#define DSH_H

// TODO: Your function definitions (declarations in dsh.h)
void messageOfDay();
void findPath(char path[]);
int shell(char* cmdline);
#endif
