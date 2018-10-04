#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAXLINE 1024
#define DELIMS " \t\r\n"
char *cmd;
pid_t child_pid;
pid_t wait_result;
int stat_loc;
char **command;


int main(int argc, char *argv[]) {
  char *cmd;
  char line[MAXLINE];
  char cmdline[MAXLINE];
  child_pid = fork();

  while (1) {
    printf("%s","wish> ");
    
    if (!fgets(line, MAXLINE, stdin)) break;

    // Parse and execute command
    if ((cmd = strtok(line, DELIMS))) {
      // Clear errors
      errno = 0;

      if (strcmp(cmd, "cd") == 0) {

        char *arg = strtok(0, DELIMS);
        if (!arg) fprintf(stderr, "Missing argument.\n");
        else chdir(arg);

      } else if (strcmp(cmd, "exit") == 0) {
        break;

      }
      if (strcmp(cmd, "path") == 1) {

        char *arg = strtok(0, DELIMS);
        chdir(arg);
      }
       else system(line);

      if (errno) perror("Failed");
    }
    
  }


  if((fgets(cmdline, MAXLINE,stdin)==NULL) && ferror(stdin))
            error("fgets error");
        if(feof(stdin)){
            printf("\n");
            exit(0);
        }   
    // The child process
   child_pid = fork();
        if (child_pid == 0) {
            /* Never returns if the call is successful */
            execvp(command[0], command);
            printf("This won't be printed if execvp is successul\n");
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        } 
             
  //readfile
  FILE *readFile;
    
    //check if user has entered a file name to read from
    if(argc < 2){

        printf("Filename is missing!\n");
	    return 0;
    }
    //Loop through user input file(s)
    for(int i=1;i<argc;i++){
        // Open file in read mode
        readFile=fopen(argv[i],"r");

        if (readFile == NULL)
        {
            //Checking if file exists
            printf("cannot open file\n",argv[i]);
        
            return 0;
        }


        // Writing content to stdout while it's not end of read file
        int result;
        while((result=fgetc(readFile))!=EOF) {
     
            putchar(result);
        }
	    printf("\n");    
        fclose(readFile);  
    }

  
}

//https://codereview.stackexchange.com/questions/180364/basic-shell-in-c?rq=1
//https://codereview.stackexchange.com/questions/117052/basic-shell-implementation?rq=1
//https://codereview.stackexchange.com/questions/67746/simple-shell-in-c
//https://codereview.stackexchange.com/questions/191914/yet-another-shell-in-c?rq=1
//https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/
//https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
//https://www.youtube.com/watch?v=k6TTj4C0LF0
//https://stackoverflow.com/questions/4788374/writing-a-basic-shell

