/*
 * Operating Systems Project 1
 * Author: 	Nanis Kanana
 * Purpose:  Implementation of the cat UNIX command
 * */
#include <stdio.h>
#include <stdlib.h> 
int main(int argc, char*argv[])
{
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

        //Checking if file exists
        if (readFile == NULL)
        {
            
            printf("my-cat: cannot open file\n");
        
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
	return 0;    
}


