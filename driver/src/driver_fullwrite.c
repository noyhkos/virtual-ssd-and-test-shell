#include <stdio.h>
#include "driver_common.h"
#include "driver_command.h"

void driver_fullwrite(unsigned int data){
    for(int i=0; i<MAX_LBA; i++){
        driver_write(i, data);
    }
}