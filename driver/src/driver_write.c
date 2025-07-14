#include <stdio.h>
#include <stdlib.h>
#include "driver_common.h"
#include "driver_command.h"

void driver_write(int lba, unsigned int data){
    char cmd[128];

    // set command
    snprintf(cmd, sizeof(cmd), "%s W %d %08X", SSD_PATH, lba, data);

    // Run system call with cmd
    if(system(cmd)==-1){
        perror("System Call Fail(driver_write)");
    }
}