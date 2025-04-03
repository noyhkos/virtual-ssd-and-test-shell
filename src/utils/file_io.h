#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdint.h>

// NAND 파일을 읽기 모드로 여는 함수
FILE* openNandFileForReading(const char *mode);

// NAND 파일을 쓰기 모드로 여는 함수
FILE* openNandFileForWriting(const char *mode);

// result.txt를 쓰기 모드로 여는 함수
FILE* openResultFileForWriting();

// result.txt를 읽기 모드로 여는 함수
FILE* openResultFileForReading();

#endif  // FILE_IO_H
