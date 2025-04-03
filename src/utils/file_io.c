#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// NAND 파일을 읽기 모드로 열기
FILE* openNandFileForReading(const char *mode) {
    FILE *nandFile = fopen("data/nand.txt", mode);
    if (nandFile == NULL) {
        perror("Error opening nand.txt for reading");
    }
    return nandFile;
}

// NAND 파일을 쓰기 모드로 열기
FILE* openNandFileForWriting(const char *mode) {
    FILE *nandFile = fopen("data/nand.txt", mode);
    if (nandFile == NULL) {
        perror("Error opening nand.txt for writing");
    }
    return nandFile;
}

// result.txt를 쓰기 모드로 열기 (기존 내용 덮어쓰기)
FILE* openResultFileForWriting() {
    FILE *resultFile = fopen("data/result.txt", "w");
    if (resultFile == NULL) {
        perror("Error opening result.txt for writing");
    }
    return resultFile;
}

// result.txt를 읽기 모드로 열기
FILE* openResultFileForReading() {
    FILE *resultFile = fopen("data/result.txt", "r");
    if (resultFile == NULL) {
        perror("Error opening result.txt for reading");
    }
    return resultFile;
}