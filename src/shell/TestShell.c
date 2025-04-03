#include <stdio.h>

#include "command_parser.h"

#define INPUT_BUFFER_SIZE 256 // 커맨드 라인 최대 256자만 받기

int main() {
    char input_line[INPUT_BUFFER_SIZE];
    ParsedCommand cmd;

    // Test shell 시작 안내내
    printf("This is Virtual SSD Test Shell!! ^^\n");
    printf("Please Type 'help' for a list of commands.\n");

    // 명령어 받기
    while(1){
        printf("SSD_TEST>> ");

        // 명령어 입력 받기
        if(fgets(input_line, sizeof(input_line), stdin)==NULL){
            break; // ctrl+D => 프로그램 종료
        }

        // 잘못된 명령어 => while문 continue;
        if(parse_command(input_line, &cmd) != 0){
            printf("INVALID COMMAND\n");
            continue;
        }

        switch (cmd.type)
        {
        case CMD_WRITE:
            break;
        
        default:
            break;
        }


    }
}