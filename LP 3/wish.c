#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    
    char *input;
    char *cmd[20];
    size_t size = 64;

    input = (char *)malloc(size*sizeof(char));

    while(1){
        printf("wish> ");
        getline(&input, &size, stdin);

        char len = strlen(input);

        if(input[len-1] == '\n'){
            input[len-1] = '\0';
	    }
        
        char *token_input; 
        token_input = strtok(input, " ");
        
        int i = 0;
        while(token_input != NULL){
            cmd[i] = token_input;
            i++;
            token_input = strtok(input, " ");
        }

        if(strcmp(cmd[0], "exit")){
            exit(0);
        }else{
            // set paths
            char *bin = "/bin/";
            char *usr_bin = "/usr/bin/";
            
            // allocate size for new path
            char *bin_path = malloc(strlen(bin)+strlen(cmd[0])+1);
            // concatenate path to new one
            strcat(bin_path, bin);
            // add command to path
            strcat(bin_path, cmd[0]);

            char *usr_bin_path = malloc(strlen(usr_bin)+strlen(cmd[0])+1);
            strcat(usr_bin_path, usr_bin);
            strcat(usr_bin_path, cmd[0]);

            // Array of commands to be passed to exec
            char *exec_array[10] = {NULL};
            
            //

            int arr_len = sizeof(cmd);

            // check for redirection
            int is_redirection = 0;

            char *output_file;

            for(int index=1;index<arr_len;index++){
                if(strcmp(cmd[index],">")){
                    is_redirection = 1;
                    // set the output file
                    index++;
                    output_file = cmd[index];
                }else{
                    exec_array[index] = cmd[index];
                }
            }

            const char *new_exec[10] = {bin_path, exec_array[1], exec_array[2], exec_array[3], exec_array[4], exec_array[5],
                                        exec_array[6], exec_array[7], exec_array[8], exec_array[9]};
            
            const char *new_exec_[10] = {usr_bin_path, exec_array[1], exec_array[2], exec_array[3], exec_array[4], exec_array[5],
                                        exec_array[6], exec_array[7], exec_array[8], exec_array[9]};
            

            pid_t pid = fork();
            if(pid==0){
                if(access(bin_path,X_OK)==0){
                    //exec_array[0] = bin_path;
                    if(is_redirection==1){
                        // redirect file
                        // freopen()
                        FILE *output_ = fopen(output_file,"w+");
                        // int save_out = fileno(output__)
                        dup2(fileno(output_), fileno(stdout));
                        dup2(fileno(output_), fileno(stderr));
                        fclose(output_);
                    }
                    execv(bin_path, new_exec);
                }else if(access(usr_bin_path,X_OK)==0){
                    //exec_array[0] = usr_bin_path;
                    if(is_redirection==1){
                        FILE *output_ = fopen(output_file,"w+");
                        dup2(fileno(output_), fileno(stdout));
                        dup2(fileno(output_), fileno(stderr));
                        fclose(output_);
                    }
                    execv(usr_bin_path, new_exec_);
                }else{
                    printf("Access denied to path");
                }
            }else{
                wait(NULL);
            }
        }
    }
    return 0;
}

