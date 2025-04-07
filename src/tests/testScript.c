#include "../../include/tests.h"
#include "../utils/file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define SSD_EXE "../../bin/ssd.exe"
#define NAND_FILE "../../data/nand.txt"
#define RESULT_FILE "../../data/result.txt"

// SSD 명령 실행 (1: 성공, 0: 실패)
int execute_ssd_command(const char* format, ...) {
    char cmd[256];
    va_list args;
    va_start(args, format);
    vsnprintf(cmd, sizeof(cmd), format, args);
    va_end(args);
    
    return system(cmd) == 0 ? 1 : 0;  // 반전된 반환 값
}

// LBA 검증 (1: 모두 일치, 0: 불일치)
int verify_lba_range(int start, int end, uint32_t expected) {
    char expected_hex[11];
    snprintf(expected_hex, sizeof(expected_hex), "0x%08X", expected);

    for(int lba = start; lba <= end; lba++) {
        if(!execute_ssd_command("%s R %d", SSD_EXE, lba)) {
            fprintf(stderr, "[ERROR] LBA %d Read Failed\n", lba);
            return 0;  // 실패 시 0 반환
        }

        FILE* fp = fopen(RESULT_FILE, "r");
        if(!fp) return 0;
        
        char actual[11] = {0};
        fgets(actual, sizeof(actual), fp);
        fclose(fp);

        if(strncmp(actual, expected_hex, 10) != 0) {
            fprintf(stderr, "[MISMATCH] LBA %d: Expected %s, Actual %s\n", 
                    lba, expected_hex, actual);
            return 0;  // 실패 시 0 반환
        }
    }
    return 1;  // 성공 시 1 반환
}

// TestApp1: 전체 쓰기/읽기 검증 (1: 성공, 0: 실패)
int testapp1() {
    system("rm -f " NAND_FILE " " RESULT_FILE);
    system("echo 0x00000000 | tee " NAND_FILE " >/dev/null 2>&1");

    const uint32_t test_value = 0xABCD1234;
    
    if(!execute_ssd_command("%s fullwrite 0x%08X", SSD_EXE, test_value)) 
        return 0;

    return verify_lba_range(0, 99, test_value);  // 1 또는 0 반환
}

// TestApp2: Write Aging 테스트 (1: 성공, 0: 실패)
int testapp2() {
    system("rm -f " NAND_FILE " " RESULT_FILE);
    system("echo 0x00000000 | tee " NAND_FILE " >/dev/null 2>&1");

    const uint32_t aging_value = 0xAAAABBBB;
    const uint32_t final_value = 0x12345678;

    for(int i=0; i<30; i++) {
        for(int lba=0; lba<=5; lba++) {
            if(!execute_ssd_command("%s W %d 0x%08X", SSD_EXE, lba, aging_value)) 
                return 0;
        }
    }

    for(int lba=0; lba<=5; lba++) {
        if(!execute_ssd_command("%s W %d 0x%08X", SSD_EXE, lba, final_value)) 
            return 0;
    }

    return verify_lba_range(0, 5, final_value);  // 1 또는 0 반환
}
