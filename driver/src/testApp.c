#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include "driver_common.h"
#include "driver_command.h"

#define TEST_STR1 "0xABCD1234"
#define TEST_DATA1 0xABCD1234
#define TEST_STR2 "0xAAAABBBB"
#define TEST_DATA2 0xAAAABBBB
#define TEST_STR3 "0x12345678"
#define TEST_DATA3 0x12345678

// lba test
int testapp1(){
    driver_fullwrite(TEST_DATA1);

    // check defect
    printf("LBA\tdata\n");
    for(int i=0; i<MAX_LBA; i++){
        char *data = driver_read(i);
        printf("%d\t%s\n",i, data);
        if(strcmp(data, TEST_STR1)!=0){
            printf("=> SSD defect at LBA:%d\n", i);
            return 0;
        }
    }

    // result
    printf("[[ SSD test was succesful ]]\n");
    printf("--- All LBAs are functioning properly ---\n");
    return 1;
}


// read/write test
int testapp2(){
    // read/write repeatedly
    for(int i=0; i<50; i++){
        for(int j=0; j<=10; j++){
            driver_write(i, TEST_DATA2);
        }
    }
    for(int i=0; i<=10; i++){
        driver_write(i, TEST_DATA3);
    }

    // check defect
    int flag = 0;
    for(int i=0; i<=10; i++){
        char *data = driver_read(i);
        printf("LBA:%d -> DATA:%s\n", i, data);
        if(strcmp(data, TEST_STR3)!=0)flag=1;
    }

    // result
    if(flag){
        printf("!!! SSD defected. read/write unable !!!\n");
        return 0;
    } else {
        printf("[[ SSD read/write properly ]]\n");
    }
    return 1;
}