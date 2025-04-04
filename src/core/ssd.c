#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../utils/file_io.h"

void WriteNand(int lba, uint32_t data) {
    // r : 읽기 모드, b : 바이너리 모드로 열기
    FILE *nandFile = openNandFileForWriting("r+b");  // 
    if (nandFile == NULL) {
        printf("Error opening NAND file for writing.\n");
        return;
    }

    // LBA 위치로 이동하여 데이터 쓰기
    // lba * sizeof(uint32_t)만큼
    // SEEK_SET : 처음부터 찾기
    fseek(nandFile, lba * sizeof(uint32_t), SEEK_SET);

    // 16진수 앞에 0x 붙이기
    char hexString[10];
    sprintf(hexString, "0x%X", data);

    // data 쓰기
    fwrite(hexString, strlen(hexString), 1, nandFile);

    // 파일 닫기
    fclose(nandFile);
}

void ReadResult(int lba) {
    FILE *nandFile = openNandFileForReading("r+b");
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
        // 0x 붙은 16진수 형태로 기록
        fprintf(resultFile, "0x%08X\n", data);
        fclose(resultFile);
    }
}

int main(int argc, char* argv[]){
    if(argv[1]=='W' && argc == 4){
        int lba = atoi(argv[2]);
        uint32_t data;
        sscanf(argv[3], "%X", data);
        WriteNand(lba, data);
    }
    else if(argv[1]=='R'&&argc==3){
        int lba = atoi(argv[2]);
        ReadResult(lba);
    }
}