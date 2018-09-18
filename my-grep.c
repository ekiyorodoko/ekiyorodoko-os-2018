#include <stdio.h>
#include <stdlib.h>

// My implementation of linux's grep function
int main(int argc, char *argv[]){
    if (argc > 1){
        // Check the parameters provided
        if(argc==2){ // only search term was provided
            char search_term = argv[1];
            char input[255];
            printf("Enter a line of text:\n");
            char text = gets(input);

            // 
        }else{
            char input[100];
            int ch;
            while((ch));
        } 

    }else{
        print("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    return 0;
}
