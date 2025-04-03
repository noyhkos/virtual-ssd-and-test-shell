#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssd.h"

// API 기능을 구현하는 파일
void handleWriteCommand(int lba, uint32_t data) {
    WriteNand(lba, data);  // WriteNand를 호출하여 데이터를 씁니다.
}

void handleReadCommand(int lba) {
    ReadFromNand(lba);  // ReadFromNand를 호출하여 데이터를 읽고 result.txt에 기록
}
