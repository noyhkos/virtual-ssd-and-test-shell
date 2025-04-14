// include/ssd.h
#ifndef SSD_H
#define SSD_H

#include <stdint.h>

void WriteNand(int lba, uint32_t data);
void ReadResult(int lba);

#endif
