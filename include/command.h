#ifndef COMMAND_H
#define COMMAND_H

// LBA 수 정의 (0~99번 총 100개)
#define LBA_COUNT 100

// LBA 하나에서 데이터 읽기 (ssd R 명령 호출 후 result.txt에서 반환된 값 리턴)
char* readCommand(int lba);

// LBA 하나에 데이터 쓰기 (ssd W 명령 호출)
void writeCommand(int lba, const char* hexData);

// 전체 LBA(100개)에서 데이터 읽기 (readCommand 반복 호출)
// 결과는 8자리 16진수 문자열 배열에 저장됨
void fullRead(char dataArray[LBA_COUNT][9]);

// 전체 LBA(100개)에 동일한 데이터 쓰기 (writeCommand 반복 호출)
void fullWrite(const char* hexData);

#endif // COMMAND_H
