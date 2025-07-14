#include <stdio.h>
// #include <string.h>
#include "driver_common.h"
#include "driver_command.h"

void driver_fullread(){
    for(int i=0; i<MAX_LBA; i++){
        printf("[%d] %s\n", i, driver_read(i));
    }
}