/*
 * Operating Systems Project 1
 * Author: 	Nanis Kanana
 * Purpose:  Implementation of the grep UNIX command
 * */
#include<stdio.h>
#include<string.h>
int main(int argc, char*argv[])
{
  char temp[200];
  char sentence[100];
  FILE *readFile;

  //check if user has entered a file name to read from
  if(argc < 2){
    printf("my-grep: searchterm [file ...]\n");
    return 1;
  }

  //If a search term, but no file, is specified
  if(argc == 2) {
		printf("\nEnter a sentence to search from: ");
    fgets(sentence, 100, stdin);
    
    if(strstr(sentence,argv[1])!= 0){
      printf("%s",sentence);
    }
    
    return 0;
		}
		
  //Loop through user input file(s)
  for(int i=2;i<argc;i++){
        // Open file in read mode
        readFile=fopen(argv[i],"r");
        //Checking if file exists
        if (readFile == NULL)
        {
            
            printf("my-grep: cannot open file\n");
        
            return 1;
        }

  char* pattern=argv[1];
  //Searching for the pattern
  while(!feof(readFile)){
    fgets(temp,1000,readFile);  
    if(strstr(temp, pattern))
      printf("%s",temp);
  }
    printf("\n");
    fclose(readFile);
  }
  return 0;
}
