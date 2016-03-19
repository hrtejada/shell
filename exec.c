//
//	EE 4374 Lab # 2 Shell (Test Function)
//	Author: Hector Tejada
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

int execute(char **cmd, int is_bg);
int redirectExecOutput(char **cmd, char *outputfile);

//Method requires a space after the command and then the & to detect run in backgroun.
//Example "ls &"
int execBackground(char **args)
{
  int i;
  i = 0;

  // traverse to the end of the tokens
  while(args[i] != 0) {
    i++;
  }

  // check for the ampersand at the end of the set of tokens
  if(args[i-1][0] == '&') {
    free(args[i-1]);
    args[i-1] = 0;  // remove the ampersand
    return 1;
  } else {
    return 0;
  }
}

int executeCmd(char **args) {
  //Command for executing change directories. If args[0] == to cd it executes change directories command.
  //Execvp does not execute cd. Use built in chdir from c library.
  if(strncmp(args[0], "cd", 2) == 0) {
    chdir(args[1]);
    return 0;
  }

  else {
    int i;
    char *output = (char *) malloc(sizeof(char) * 256);
    int isOut;
    int outfd;

    // Look for output redirection symbol
    for(i = 0; args[i] != 0; i++) {
      if(args[i][0] == '>') {
        strcpy(output, args[i+1]);
        args[i] = NULL;
        isOut = 1;
        break;
      }
    }

    // Redirect if detected, else execute normally
    if(isOut == 1){
      redirectExecOutput(args, output);
    } else {
      execute(args, execBackground(args) );
    }
  }

  return 0;
}

//Method to execute the actual command that is
int execute(char **args, int background){

  pid_t pid;
  int status;

  // Failed fork
  if((pid = fork())< 0){
    printf("ERROR");
    exit(1);
  }

  // Child process
  else if(pid == 0) {
    if(execvp(*args, args) < 0) {
      printf("Exec failed\n");
      exit(1);
    }
  }

  // Parent process
  else{
    // If background is set (background = 1), parent does not wait. If not set (background = 0) it waits.
    if(background == 0) {
      while(wait(&status)!=pid);
    }
  }

  return 0;
}

//Method for executing commands and redirecting output to file.
int redirectExecOutput(char **cmd, char *outputfile) {
  int file_fd;
  int stdout_fd;

  // Check that outputfile is valid and open if so..
  if(outputfile == NULL)
    return 0;
  if((file_fd = open(outputfile, O_WRONLY | O_TRUNC | O_CREAT, 0600)) == -1)
    return -1;

  // Save stdout for later
  stdout_fd = dup(1);

  // Redirect stdout to file descriptor for output file
  if (dup2(file_fd, STDOUT_FILENO) == -1) {
    close(file_fd);
    close(stdout_fd);
    return -1;
  }

  // Execute CMD
  execute(cmd, 0);

  // Restore STDOUT
  dup2(stdout_fd, 1);

  // Close file and file descriptors
  close(file_fd);
  close(stdout_fd);

  return 0;
}
