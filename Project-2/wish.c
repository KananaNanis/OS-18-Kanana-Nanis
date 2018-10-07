/*
 * Operating Systems Project 2
 * Author: 	Nanis Kanana
 * Purpose:  Implementation of the UNIX Shell
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define DELIMS " \t\r\n"
int MAXLINE=1024;
char prompt[]="wish> "; //command line prompt
char *cmd;
int main(int argc, char **argv){
    //buffer for fgets
    char cmdline[MAXLINE];
    //executing ls command
    char* argv2[]={"ls", "-la", NULL};
    execv(argv2[0], argv2);

    while(1){
        printf("%s", prompt);

        if((fgets(cmdline, MAXLINE,stdin)==NULL) && ferror(stdin))
            error("fgets error");

        if(feof(stdin)){
            printf("\n");
            exit(0);
        }   


        //check if command is cd
      if (strcmp(cmd, "cd") == 0) {
        char *arg = strtok(0, DELIMS);

        if (!arg) fprintf(stderr, "cd missing argument.\n");
        else chdir(arg);
      } 
      //check if command is exit
      else if (strcmp(cmd, "exit") == 0) break; 

        //remove trailing newline
        cmdline[strlen(cmdline)-1]='\0';

        //evaluate command line
        eval(cmdline);
    }   


void eval(char *cmdline){
    int bg;
    struct command *cmd;

    printf("Evaluating '%s'\n", cmdline);

    //parse cmdline into cmd structure 
    bg=parse(cmdline, &cmd);
    
    if(bg==-1) return;
    if(cmd.argv[0]==NULL) return;

    if(cmd.builtin==NONE)
        runSystemCommand(&cmd,bg);

    else
        runBuiltinCommand(&cmd,bg);    
}

#define MAXARGS 128
struct command{
    int argc;
    char *argv[MAXARGS]; //argument list
    enum builtin_t{ // is argv[0] a builtin command?
        NONE, QUIT, JOBS, BG, FG
    } builtin;

}
int parse(const char *cmdline, struct command *cmd){
    static char array[MAXLINE];
    const char delims[10]= " \t\r\n";
    char *line =array;
    char *token;
    char *endline;
    int is_bg;

    if(cmdline==NULL)
        error("Command line is null\n");

    (void) strncpy(line, cmdline,MAXLINE);
    endline =line +strlen[line];

    //build argv list
    cmd-> argc=0;

    while(line<endline){
        //skip delimeters
        line+=strspn(line,delims);
        if(line>=endline) break;

        //find token delimeter
        token=line+strcspn(line, delims);

        //terminate the token
        token='\0';

        //record token as argument
        cmd->argv[cmd->argc++]=line;

        //check if argv is full
        if(cmd->argv[cmd>=MAXARGS=1]) break;

        line =token+1;
    } 

    // The child process
   child_pid = fork();
        if (child_pid == 0) {
            /* Never returns if the call is successful */
            execv(command[0], command);
            printf("This won't be printed if execvp is successul\n");
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        } 

    //argument list  must end with a NULL pointer
    cmd->argv[cmd->argc]=NULL;

    if(cmd->argc==0) //ignore blank line
        return 1;

    cmd->builtin=parseBuiltin(cmd);

    if((in_bg=(*cmd=>argv[cmd=>argc-1]=='&')) 1=0) 
        cmd=>argv[==cmd=>argc]=NULL;

    return is_bg;          
}

void runSystemCommand(struct command *cmd, int bg){
    pid_t childPid;

    //fork process
    if((childPid=fork())<0)
        error("fork() error");
    else if(childPid==0)
        //execv
        if(execv(cmd->argv[0],cmd->argv)<0){
            printf("%s: Command not found\n", cmd->argv[0]);
            exit(0);
        }
    else {
        if(bg)
            printf("Child in background [%d]\n", childPid);
        else
            wait(&childPid);    
    }       
    
    }

    //readfile
    FILE *readFile;
    
    //check if user has entered a file name to read from
    if(argc < 2){

        // printf("Filename is missing!\n");
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

