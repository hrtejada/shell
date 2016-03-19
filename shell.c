//
//	EE 4374 Lab # 2 Shell (Test Function)
//	Author: Hector Tejada
//


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "htejada_argtok.h"
#include "htejada_exec.h"

int main()
{
  int i;
	int inputSize;
	char buff[128];		// Character buffer
	char **args;	// Character buffer

  write(1, "Welcome to Hector Tejada's Shell (type 'x' to exit)\n", 52);

  while(1)
	{
		// Request a line of input
		write(1, "\nshell -> ", 10);

    inputSize = read(0, buff, 128);
    // Strip off carriage return
		buff[inputSize-1] = '\0';

		if(buff[0] == 0)
			continue;

		if((buff[0] == 'x') && (buff[1] == '\0'))
		{
			exit(0);
		}

		// make the argument vector
		args = argtok(buff, ' ');

		// execute the command
		executeCmd(args);

    free(args);

	}

	return 0;

}
