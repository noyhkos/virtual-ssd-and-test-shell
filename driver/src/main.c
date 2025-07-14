#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "driver_command.h"

#define BUF_SIZE 256

int is_valid_hex_data(const char *str){
    if(strlen(str) != 10) return 0;
    if(!( (str[0]=='0') && (str[1]=='x'||str[1]=='X') )){
        return 0;
    }
    for(int i = 2; i < 10; i++){
        if ((str[i] >= '0' && str[i] <= '9') ||
            (str[i] >= 'A' && str[i] <= 'F') ||
            (str[i] >= 'a' && str[i] <= 'f')) continue;
        else return 0;
    }
    return 1;
}

int main(){
    printf("[[ Virture SSD Driver ]] \n");
    printf("Type 'help' for available commands.\n");

    char buf[BUF_SIZE];
    while(1){
        // Get input from user
        printf(">> ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("\nError: Command input error.\n");
            break;
        }

        // remove remaining charaters in input buffer
        if(!strchr(buf, '\n')){
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF);
        }

        // \n => \0
        buf[strcspn(buf, "\n")] = '\0';

        // get command word
        char *cmd = strtok(buf, " ");
        if(!cmd)continue;
        if(strcmp(cmd, "write")==0){
            // lba valid check
            char *lba_ = strtok(NULL, " ");
            if(!lba_){
                fprintf(stderr, "Error: No lba\n");
                continue;
            }
            char *endptr;
            int lba = strtol(lba_, &endptr, 10);
            if(endptr == lba_ || *endptr != '\0'){
                fprintf(stderr, "Error: Invalid LBA\n");
                continue;
            } 
            if(lba<0 || lba>=MAX_LBA){
                fprintf(stderr, "Error: LBA out of range\n");
                continue;
            }

            // data valid check
            char *data_ = strtok(NULL, " ");
            if(!data_){
                fprintf(stderr, "Error: No data\n");
                continue;
            }
            if(!is_valid_hex_data(data_)){
                fprintf(stderr, "Error: Invalid Data format\n");
                printf("ex) Data: 0xABCD1234\n");
                continue;
            }
            unsigned int data = strtol(data_, &endptr, 16);
            if(endptr == data_ || *endptr != '\0'){
                fprintf(stderr, "Error: Data type changing error.\n");
                continue;
            } 

            // run command
            driver_write(lba, data);

        } else if(strcmp(cmd, "read")==0){
            // lba valid check
            char *lba_ = strtok(NULL, " ");
            if(!lba_){
                fprintf(stderr, "Error: No lba\n");
                continue;
            }
            char *endptr;
            int lba = strtol(lba_, &endptr, 10);
            if(endptr == lba_ || *endptr != '\0'){
                fprintf(stderr, "Error: Invalid LBA\n");
                continue;
            } 
            if(lba<0 || lba>=MAX_LBA){
                fprintf(stderr, "Error: LBA out of range\n");
                continue;
            }

            // run command
            char *rst = driver_read(lba);
            if(rst)printf("%s\n", rst);

        } else if(strcmp(cmd, "fullwrite")==0){
            // data valid check
            char *data_ = strtok(NULL, " ");
            if(!data_){
                fprintf(stderr, "Error: No data\n");
                continue;
            }
            if(!is_valid_hex_data(data_)){
                fprintf(stderr, "Error: Invalid Data format\n");
                printf("ex) Data: 0xABCD1234\n");
                continue;
            }
            char *endptr;
            unsigned int data = strtol(data_, &endptr, 16);
            if(endptr == data_ || *endptr != '\0'){
                fprintf(stderr, "Error: Data type changing error.\n");
                continue;
            } 

            // run command
            driver_fullwrite(data);
        } else if(strcmp(cmd, "fullread")==0){
            // run command
            driver_fullread();
        } else if(strcmp(cmd, "testapp1")==0){
            testapp1();
        } else if(strcmp(cmd, "testapp2")==0){
            testapp2();
        } else if(strcmp(cmd, "exit")==0 || strcmp(cmd, "quit")==0){
            break;
        } else if(strcmp(cmd, "help")==0){
            printf("\n[[ Available Commands ]]\n");
            printf("  write [LBA] [DATA]     : Write 4-byte data to LBA (ex: write 3 0x12345678)\n");
            printf("  read [LBA]             : Read 4-byte data from LBA (ex: read 3)\n");
            printf("  fullwrite [DATA]       : Fill all 100 blocks with DATA (ex: fullwrite 0xFFFFFFFF)\n");
            printf("  fullread               : Read all 100 blocks and display\n");
            printf("  testapp1               : Run test pattern 1\n");
            printf("  testapp2               : Run test pattern 2\n");
            printf("  help                   : Show this help message\n");
            printf("  exit                   : Exit the driver shell\n\n");
        }else {
            fprintf(stderr, "Error: Invalid Command '%s'.\n", cmd);
            printf("Type 'help' for available commands.\n");
            continue;            
        }

        


    }
}