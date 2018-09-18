#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// My implementation of linux's grep function
int main(int argc, char *argv[]){

    // Check the parameters provided
    if (argc == 1){ //no command given
        printf("my-grep: searchterm [file ...]\n");
        exit(1);

    }else{
        // Get the search term
        char *search_term = argv[1];
        //char *text;

        if(argc == 2){ // only search term was provided
            // Give user access to console to type query
            char input[255];
            printf("Enter a line of text:\n");
            char *as = fgets(input, sizeof input, stdin);
            // Check if search term is in the text provided by user
            char* status = strstr(as, search_term);
            if(status==NULL){
                exit(0);
            }else{
                printf(input);
            }
        }else{
            FILE *fp;
            for (int i = 2; i < argc; i = i + 1){
                fp = fopen(argv[i], "r");
                //c check if file exists
                if(fp == NULL){
                    printf("my grep: cannot open file\n");
                    exit(1);
                }else{
                    char input[512];
                    printf("--%s--\n", argv[i]);
                    // read the file
                    while(fgets(input, sizeof input, fp)!=NULL){
                        //Check if search term is in the text provided by user
                        char* status = strstr(input, search_term);
                        if(status==NULL){
                            continue;
                        }else{
                            printf(input);
                        }
                    }
                    printf("\n");
                }
                fclose(fp);
            }
        }
    }
    return 0;
}