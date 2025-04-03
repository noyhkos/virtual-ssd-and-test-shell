// src/shell/TestShell.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./command_parser.h"
#include "include/command.h"
#include "include/tests.h"

void print_help() {
    printf("Available commands:\n");
    printf("  write [LBA] [0x12345678]  : Write 4-byte hex data to LBA\n");
    printf("  read [LBA]                : Read data from LBA\n");
    printf("  fullwrite [0x12345678]    : Write same data to all LBAs\n");
    printf("  fullread                  : Read all LBA data and display\n");
    printf("  testapp1                  : Run test application 1\n");
    printf("  testapp2                  : Run test application 2\n");
    printf("  help                      : Show this help message\n");
    printf("  exit                      : Exit shell\n");
}

void run_shell() {
    char input[256];
    ParsedCommand cmd;

    printf("==== Virtual SSD Shell ====\n");
    printf("Type 'help' for available commands.\n");

    while (1) {
        printf(">> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error. Exiting...\n");
            break;
        }

        // 입력 오류 처리
        if (parse_command(input, &cmd) != 0) {
            printf("INVALID COMMAND\n");
            continue;
        }

        switch (cmd.type) {
            case CMD_WRITE:
                writeCommand(cmd.lba, cmd.data);
                break;

            case CMD_READ: {
                char* result = readCommand(cmd.lba);
                if (result) printf("[%02d] %s\n", cmd.lba, result);
                else printf("Error reading LBA %d\n", cmd.lba);
                break;
            }

            case CMD_FULLWRITE:
                fullWrite(cmd.data);
                break;

            case CMD_FULLREAD: {
                char dataArray[LBA_COUNT][9];
                fullRead(dataArray);
                for (int i = 0; i < LBA_COUNT; i++) {
                    printf("[%02d] %s\n", i, dataArray[i]);
                }
                break;
            }

            case CMD_TESTAPP1:
                if (testapp1()) printf("testapp1: PASS\n");
                else printf("testapp1: FAIL\n");
                break;

            case CMD_TESTAPP2:
                if (testapp2()) printf("testapp2: PASS\n");
                else printf("testapp2: FAIL\n");
                break;

            case CMD_HELP:
                print_help();
                break;

            case CMD_EXIT:
                printf("Bye!\n");
                return;

            default:
                printf("INVALID COMMAND\n");
                break;
        }
    }
}

int main() {
    run_shell();
    return 0;
}
