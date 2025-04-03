#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssd.h"
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

    // data 쓰기
    fwrite(&data, sizeof(uint32_t), 1, nandFile);

    // 파일 닫기기
    fclose(nandFile);
}

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

int main(int argc, char* argv[]){
    if(argv[1]=='W' && argc == 4){
        int lba = atoi(argv[2]);
        WriteNand(lba, argv[3]);
    }
    else if(argv[1]=='R'&&argc==3){
        int lba = atoi(argv[2]);
        ReadFromNand(lba);
    }
}