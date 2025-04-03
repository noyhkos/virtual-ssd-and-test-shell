#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/utils/file_io.h"  // result.txt 읽기 유틸 함수 포함
#include "command.h" 

#define MAX_LINE 256
#define LBA_COUNT 100
#define SSD_PATH "./bin/ssd.exe"  // ssd 실행 파일 경로

// LBA 위치에서 데이터를 읽고 result.txt에 저장된 결과를 반환하는 함수
char* readCommand(int lba) {
    char command[MAX_LINE];

    // ssd read 명령어 문자열 생성: 예) "./bin/ssd.exe R 33"
    snprintf(command, sizeof(command), "%s R %d", SSD_PATH, lba);

    // 명령어 실행: result.txt에 결과 저장됨
    system(command);

    // result.txt 파일 열기
    FILE *resultFile = openResultFileForReading();
    if (!resultFile) return NULL;

    static char buffer[9]; // 8자리 16진수 + null 문자('\0')
    if (fgets(buffer, sizeof(buffer), resultFile) == NULL) {
        perror("result.txt 읽기 실패");
        fclose(resultFile);
        return NULL;
    }

    fclose(resultFile);
    return buffer;  // 읽은 데이터 문자열 반환
}

// 주어진 LBA에 8자리 16진수 데이터를 쓰는 함수
void writeCommand(int lba, const char* hexData) {
    char command[MAX_LINE];

    // ssd write 명령어 문자열 생성: 예) "./bin/ssd.exe W 33 0x12345678"
    snprintf(command, sizeof(command), "%s W %d %s", SSD_PATH, lba, hexData);

    // 명령어 실행: 해당 LBA에 데이터 저장됨
    system(command);
}

// 전체 LBA(0~99)에 대해 readCommand를 반복 수행하고 결과를 배열에 저장
void fullRead(char dataArray[LBA_COUNT][9]) {
    for (int i = 0; i < LBA_COUNT; i++) {
        char* result = readCommand(i);
        if (result) {
            strncpy(dataArray[i], result, 9);  // 최대 8자리 복사 + null 포함
        } else {
            strncpy(dataArray[i], "ERROR", 6); // 오류 시 문자열 저장
        }
    }
}

// 전체 LBA(0~99)에 대해 같은 데이터를 반복해서 writeCommand로 저장
void fullWrite(const char* hexData) {
    for (int i = 0; i < LBA_COUNT; i++) {
        writeCommand(i, hexData);
    }
}
