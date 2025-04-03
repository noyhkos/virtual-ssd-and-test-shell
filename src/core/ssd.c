#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssd.h"
#include "file_io.h"

// WriteNand 함수 구현
void WriteNand(int lba, uint32_t data) {
    FILE *nandFile = openNandFileForWriting("r+b");  // 'r+b'로 파일을 열기
    if (nandFile == NULL) {
        printf("Error opening NAND file for writing.\n");
        return;
    }

    // LBA 위치로 이동하여 데이터 쓰기기
    fseek(nandFile, lba * sizeof(uint32_t), SEEK_SET);
    fwrite(&data, sizeof(uint32_t), 1, nandFile);
    fclose(nandFile);
}

// ReadFromNand 함수 구현
void ReadFromNand(int lba) {
    FILE *nandFile = openNandFileForReading("rb");  // 'rb'로 파일 열기
    if (nandFile == NULL) {
        printf("Error opening NAND file for reading.\n");
        return;
    }

    uint32_t data;
    fseek(nandFile, lba * sizeof(uint32_t), SEEK_SET);
    fread(&data, sizeof(uint32_t), 1, nandFile);
    fclose(nandFile);

    // result.txt에 데이터를 기록하는 기능
    FILE *resultFile = openResultFileForWriting();
    if (resultFile != NULL) {
        fprintf(resultFile, "0x%08X\n", data);
        fclose(resultFile);
    }
}
