#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void handleWriteCommand(int lba, uint32_t data) {
    WriteNand(lba, data);  // WriteNand를 호출하여 데이터 쓰기기
}

void handleReadCommand(int lba) {
    ReadResult(lba);  // ReadFromNand를 호출하여 데이터를 읽고 result.txt에 기록
}
