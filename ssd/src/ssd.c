#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssd_common.h"
#include "ssd_command.h"


// main argument:
// 1. cmd -> R(read) , W(write)
// 2. lba number -> integer, 0~99
// 3. (with W cmd only)data -> 8 hexadecimal characters. ex) 1234ABCD 

void usage(){
	printf("Usage:\n");
    printf("  ssd W [LBA: 0~99] [DATA: 0x12345678]\n");
    printf("  ssd R [LBA: 0~99]\n");
}

int is_valid_hex_data(const char *str){
    if(strlen(str) != 8) return 0;
    for(int i = 0; i < 8; i++){
        if ((str[i] >= '0' && str[i] <= '9') ||
            (str[i] >= 'A' && str[i] <= 'F') ||
            (str[i] >= 'a' && str[i] <= 'f')) continue;
        else return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){
	// argument valid check
	if(argc<3){
		usage();
		return 1;
	}

	// command valid check
	char cmd = argv[1][0];	
	if(cmd != 'R' && cmd != 'W'){
		fprintf(stderr, "Error: Invalid Command\n");
	}

	// lba valid check
	char *endptr;
	int lba = strtol(argv[2], &endptr, 10);
    if(endptr == argv[2] || *endptr != '\0'){
        fprintf(stderr, "Error: Invalid LBA\n");
    } 
    if(lba<0 || lba>=MAX_LBA){
        fprintf(stderr, "Error: LBA out of range\n");
    }

	// run command
	if(cmd=='R'){ // read command
        if (argc != 3){
            fprintf(stderr, "Error: Invalid read command.\n");
            usage();
            return 1;
        }
		ssd_read(lba);
	} else if(cmd=='W'){ // write command
		if (argc != 4 || !is_valid_hex_data(argv[3])) {
            fprintf(stderr, "Error: wrong data format.\n");
            usage();
            return 1;
        }
        unsigned int data = (unsigned int)strtoul(argv[3], NULL, 16);
		ssd_write(lba, data);
	} else {
        fprintf(stderr, "Error: Unknown command '%s'\n", argv[1]);
        usage();
        return 1;
	}

}
