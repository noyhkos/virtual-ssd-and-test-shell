#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

// 커맨드 종류 enum
typedef enum{
    CMD_UNKNOWN,
    CMD_WRITE,
    CMD_READ,
    CMD_EXIT,
    CMD_HELP,
    CMD_FULLWRITE,
    CMD_FULLREAD,
    CMD_TESTAPP1,
    CMD_TESTAPP2
}CommandType;


// 종합 커맨드 구조체체
typedef struct {
    CommandType type;
    int lba;
    char data[11];
}ParsedCommand;


// 커맨드 파싱함수 원형 선언
int parse_command(const char *input, ParsedCommand *result);


#endif