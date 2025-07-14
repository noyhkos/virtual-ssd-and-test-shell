#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "driver_common.h"
#include "driver_command.h"

char *driver_read(int lba){
    char cmd[128];

    // set command
    snprintf(cmd, sizeof(cmd), "%s R %d", SSD_PATH, lba);

    // Run system call with cmd
    if(system(cmd)==-1){
        perror("System Call Fail(driver_read)");
        return NULL;
    }

    // open result.txt
    int fd = open(RESULT_PATH, O_RDONLY);
    if(fd<0){
        perror("open result.txt");
        return NULL;
    }

    // get 4 bytes
    unsigned char buf[4];
    ssize_t n = read(fd, buf, 4);
    close(fd);
    if(n != 4){
        fprintf(stderr, "Error: result.txt read failed (read %zd bytes)\n", n);
        return NULL;
    }

    // change to hex string
    static char result_str[11];  // "0x" + 8 digits + '\0'
    snprintf(result_str, sizeof(result_str), "0x%02X%02X%02X%02X",
             buf[3], buf[2], buf[1], buf[0]); // Little Endian

    return result_str;

    
}