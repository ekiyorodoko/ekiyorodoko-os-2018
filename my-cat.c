#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    // Loop to read file
    if(argc > 1){
        FILE *fp;
        // Loop over arguments
        for (int i = 1; i < argc; i=i+1){
            
            // code segment to read file
            fp = fopen(argv[i], "r");

            // check if file is null
            if(fp == NULL){
                printf("cannot open file\n");
                exit(1);
                //return EXIT_FAILURE;
            }else{
                printf("--%s--\n", argv[i]);
                // read the file
                char input[512];
                while(fgets(input, sizeof input, fp)){
                    printf(input);
                }
                // int ch;

                // while((ch=getchar())!=EOF){
                //     input = putchar(ch)
                // }
            }
            printf("\n\n");
        }
        fclose(fp);
    }
    return 0;    
}
    



