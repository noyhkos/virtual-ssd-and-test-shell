#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ssd_common.h"
#include "ssd_command.h"

void ssd_write(int lba, unsigned int data){

    // open/create nand.txt
    int fd = open(NAND_PATH, O_RDWR | O_CREAT, 0644);
    if(fd < 0){
        perror("open nand.txt");
        return;
    }

    // set offset to lba address
    off_t offset = lba * BLOCK_SIZE;
    if(lseek(fd, offset, SEEK_SET) == -1){
        perror("lseek");
        close(fd);
        return;
    }

    // Save data to buffer
    // This part make it easy to switch little/big endian sys.
    unsigned char buf[BLOCK_SIZE];
    buf[0] = (data >> 0) & 0xFF;     // LSB
    buf[1] = (data >> 8) & 0xFF;
    buf[2] = (data >> 16) & 0xFF;
    buf[3] = (data >> 24) & 0xFF;    // MSB

    if(write(fd, buf, 4) != 4){
        perror("write");
    }

    close(fd);
}