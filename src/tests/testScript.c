#include <stdio.h>
#include <stdint.h>

#include "../../include/commands.h"

int testApp1(uint32_t data){
    Fullwrite(data);
    Fullread(data);
}


int testApp2(uint32_t data){
    for(int i=0;i<30;i++){
        for(int i=0;i<6;i++){
            ssd_write(i,0xAAAABBBB);
        }
    }

    for(int i=0;i<6;i++){
        ssd_write(i,0x12345678);
    }
    
    for(int i=0;i<6;i++){
        ssd_read(i);
    }

}
