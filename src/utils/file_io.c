#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// nand.txt 경로
#define NAND_PATH "./data/nand.txt"

// result.txt 경로
#define RESULT_PATH "./data/result.txt"

// NAND 파일을 읽기 모드로 열기
FILE* openNandFileForReading(const char *mode) {
    FILE *nandFile = fopen(NAND_PATH, mode);
    if (nandFile == NULL) {
        perror("Error opening " NAND_PATH " for reading");
    }
    return nandFile;
}

// NAND 파일을 쓰기 모드로 열기
FILE* openNandFileForWriting(const char *mode) {
    FILE *nandFile = fopen(NAND_PATH, mode);
    if (nandFile == NULL) {
        perror("Error opening " NAND_PATH " for writing");
    }
    return nandFile;
}

// result.txt를 쓰기 모드로 열기 (기존 내용 덮어쓰기)
FILE* openResultFileForWriting() {
    FILE *resultFile = fopen(RESULT_PATH, "w");
    if (resultFile == NULL) {
        perror("Error opening " RESULT_PATH " for writing");
    }
    return resultFile;
}

// result.txt를 읽기 모드로 열기
FILE* openResultFileForReading() {
    FILE *resultFile = fopen(RESULT_PATH, "r");
    if (resultFile == NULL) {
        perror("Error opening " RESULT_PATH " for reading");
    }
    return resultFile;
}
