#ifndef TESTS_H
#define TESTS_H

#include <stdint.h>
// 테스트 함수 프로토타입
int testapp1(void);
int testapp2(void);
int verify_lba_range(int start, int end, uint32_t expected);

#endif // TESTS_H
