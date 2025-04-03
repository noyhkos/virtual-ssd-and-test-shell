#ifndef SSD_H
#define SSD_H

#include <stdint.h>

// LBA(논리 블록 주소) 관련 상수
#define MAX_LBA 100  // 최대 LBA (0 ~ 99)

// 함수 프로토타입
void WriteNand(int lba, uint32_t data);
void ReadFromNand(int lba);

#endif // SSD_H
