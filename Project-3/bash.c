#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
//main function to run all the arguments
int main(int argc, char *argv[]) 
{ 
		FILE *stream;
		char *ln = NULL;
		size_t len = 32;
    	ssize_t nread;
    	if (argc==1)
    	{
    		while(1){
				printf("%s", "wish> ");
				getline (&ln,&len,stdin);
				newlineRemove(ln);	
				const char s[2] = "&";
				char *commands[10];
				char *token;
			   token = strtok(ln, s);
			   int count = 0;
			   while( token != NULL ) {
			      commands[count] = token;
			      count = count+1;
			      token = strtok(NULL, s);
			   }
			   	int i,j; 
				pthread_t thread_id[count]; 
				 for (i = 0; i < count; i++){
				 	pthread_create(&thread_id[i], NULL, executeCommands, commands[i]); 
				 	pthread_mutex_lock(&running_mutex);
				    running_threads++;
				    pthread_mutex_unlock(&running_mutex);				 	
				 } 		
				while (running_threads > 0)
				  {
				     sleep(1);
				  }
			}
		}
		//open file and print error message
		else if(argc ==2){
			stream = fopen(argv[1], "r");
			if (stream == NULL) {
				errorMessage();
			    exit(1);
			 }
			 while ((nread = getline(&ln, &len, stream)) != -1) {		
			    newlineRemove(ln);
			    const char s[2] = "&";
				char *commands[10];
				char *token;
			   token = strtok(ln, s);
			   int count = 0;
			   while( token != NULL ) {
			      commands[count] = token;
			      count = count+1;
			      token = strtok(NULL, s);
			   }
			   	int i,j; 
				pthread_t thread_id[count];
				 for (i = 0; i < count; i++){
				 	pthread_create(&thread_id[i], NULL, executeCommands, commands[i]); 
				 	pthread_mutex_lock(&running_mutex);
				    running_threads++;
				    pthread_mutex_unlock(&running_mutex);				 	
				 }		
				while (running_threads > 0)
				  {
				     sleep(1);
				  }

			 }
		}
		else{
			printf("%s\n", "Error: Check your input");
		}

	 return 0; 
} 
void newlineRemove(char *ln)
{
    int newLine = strlen(ln) -1;
    if (ln[newLine] == '\n')
        ln[newLine] = '\0';
}

char* concat(const char *first, const char *second)
{
    const size_t fir_len = strlen(first);
    const size_t sec_len = strlen(second);
    char *output = malloc(fir_len + sec_len + 1); 
    memcpy(output, first, fir_len);
    memcpy(output + fir_len, second, sec_len + 1); 
    return output;
}

void errorMessage(){
	char errorMess[30] = "An error has occurred\n"; write(STDERR_FILENO, errorMess, strlen(errorMess)); 
}
volatile int running_threads = 0;
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;
void *executeCommands(void *l){
    char *paths[10];
    char *line = (char *) l;
    paths[0] = "/bin";
	paths[1] = "/usr/bin";
	int numPaths = 2;
	newlineRemove(line);			
	const char s[2] = " ";
	char *arg[10];
	char *token;
   token = strtok(line, s);
   int count = 0;
   while( token != NULL ) {
      arg[count] = token;
      count = count+1;
      token = strtok(NULL, s);
   }
	if (strcmp(arg[0], "path") == 0){
		numPaths = 0;
		for(int j = 1;j<count;j++){
				paths[j-1] = malloc(strlen(arg[j])+1);
				strcpy(paths[j-1], arg[j]);
				numPaths = numPaths +1;
		}	
	}
    else if(strcmp(arg[0], "exit") == 0){
		exit(0);
	}
	else if (strcmp(arg[0], "cd") == 0)
	{
	   if (count==2){
	   	if (chdir(arg[1])==0){
	   		printf("%s\n","in folder now");
	   	}
	   	else{
	   		errorMessage();
	   	}
	   }
	   else{
	   		errorMessage();
	   }
	}
	else{
	    char *array[10];
	    for (int i = 1; i<11;i++){
	    	array[i]=NULL;
	    }	
		//Find the redirect symbol and put arguments in array for execv	
		int redirect = 0; 
		char *filename; 
		if(count>1){
			for(int i=1;i<count;i++){
				if (strcmp(arg[i], ">") != 0){
					array[i] = arg[i];
				}
				else{
					redirect = 1;
					i++;
					filename = arg[i];
				}
			}
		}
		//Initialize rc to fork function and redirect the results to the output file
		int rc = fork();
		if (rc==0){
			for (int k = 0;k<numPaths;k++){
				char *pathC = concat(paths[k],"/");
				char *path = concat(pathC,arg[0]);
				array[0] = path;
				if (access(path,X_OK)==0){	
					if (redirect == 1){
						FILE* file = fopen(filename, "w+");
					   dup2(fileno(file), fileno(stdout));
					   dup2(fileno(file), fileno(stderr));
					   fclose(file);
					}
					execv(path, array);
				}
			}
			errorMessage();
		}
		else
		{
			wait(NULL);
		}
	}
	//put locks on the running threads
	pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
}
