#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ssd_common.h"
#include "ssd_command.h"

void ssd_read(int lba){

    // open|create nand.txt
    int nand_fd = open(NAND_PATH, O_RDWR | O_CREAT, 0644);
    if(nand_fd < 0){
        perror("open nand.txt");
        return;
    }

    // open|create result.txt
    int result_fd = open(RESULT_PATH, O_RDWR | O_CREAT, 0644);
    if(result_fd < 0){
        perror("open result.txt");
        return;
    }

    // set offset to lba address
    off_t offset = lba * BLOCK_SIZE;
    if(lseek(nand_fd, offset, SEEK_SET) == -1){
        perror("lseek");
        close(nand_fd);
        return;
    }

    // read a block
    unsigned char buf[BLOCK_SIZE];
    ssize_t n = read(nand_fd, buf, BLOCK_SIZE);
    if(n < 0){
        perror("read");
        close(nand_fd);
        return;
    } else {
        for(int i=n; i<BLOCK_SIZE; i++)buf[i]=0;
    }
    close(nand_fd);
    // printf("Wrtie 0x%02X%02X%02X%02X to result.txt at LBA = %d\n", buf[3], buf[2], buf[1], buf[0], lba);


    // write to result.txt
    for(int i=0; i<BLOCK_SIZE; i++){
        if(write(result_fd, buf+i, 1)<0){
            perror("write result.txt");
            break;
        }
    }
    close(result_fd);
}