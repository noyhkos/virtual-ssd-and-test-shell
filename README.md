# Virtual SSD and Test Shell
# [가상 SSD와 테스트를 위한 커스텀 쉘 개발 프로젝트]

## 1. 구조

- **운영체제**: Ubuntu 20.04  
- **언어**: C (gcc), Shell Script (bash)  
- **프로젝트 디렉토리**: `~/ssdTest/`  
- **필수 파일**: `ssd.c`, `TestShell.c`, `nand.txt`, `result.txt`, `testScript`

### 설명

- 가상 SSD 프로그램은 파일 입출력을 실행한다.
- TestShell을 이용해 SSD에 여러 가지 명령을 보낼 수 있다.
- SSD는 `nand.txt`와 `result.txt`에 결과를 저장하는 단순한 작업을 수행한다.


## 2. 기능별 설명

### 2.1 ssd.c

- 4Byte 단위 Logical Block
- 0~99번 총 100개의 Logical Block (총 400Byte)
- 명령어:
  - `W`: 예) `ssd W 33 0x12345678` → 33번 LBA에 값 저장
  - `R`: 예) `ssd R 33` → 33번 LBA 읽고 `result.txt`에 저장
- LBA: 0~99 (10진수)
- DATA: `0x`로 시작하는 8자리 16진수 (`0x00000000` 형식)

### 2.2 nand.txt

- 4Byte × 100개 = 400Byte 저장공간 확보 필요
- 처음에 모든 bit는 0으로 초기화

### 2.3 result.txt

- 읽기 명령어 실행 시 4Byte 데이터를 저장
- 매 호출마다 덮어쓰기 초기화됨

### 2.4 TestShell.c

- 명령어 지원:
  - `write [LBA] [Data]`
  - `read [LBA]`
  - `exit`, `help`
  - `fullwrite [Data]`: 전체 LBA에 동일 값 쓰기
  - `fullread`: 전체 LBA 출력
  - `testapp1`, `testapp2`
- 포맷 체크 엄격:
  - LBA: 0~99
  - DATA: `0x`로 시작하는 8자리 16진수
- 잘못된 명령어는 `INVALID COMMAND` 출력 (Segfault 금지)

### 2.5 testScript.c

- `testapp1`:
  1. `fullwrite("0x1234ABCD")`
  2. `fullread`로 SSD 정상작동 여부 확인
  3. 결과 출력

- `testapp2`:
  1. 0~5 LBA에 `0xAAAABBBB`을 30회 write
  2. 같은 위치에 `0x12345678` write
  3. read로 확인, 결과 출력
  4. 

## 3. 주안점

1. 문자열 Parsing을 포함한 파일 입출력
2. Structure & Union을 통한 Binary 데이터 관리
3. Byte/Bit 단위 Parsing
4. 팀 프로젝트를 위한 컴파일 분할
5. 협업을 위한 소스/헤더 구조 설계
6. Shell Script 및 Makefile을 활용한 빌드 자동화


## 프로젝트 디렉토리 구조

```plaintext
~/ssdTest/
├── testShell.exe
├── bin/
│   └── ssd.exe
├── src/
│   ├── ssd/
│   │   ├── ssd.c
│   │   └── ssd_api.c
│   ├── shell/
│   │   ├── TestShell.c
│   │   ├── command.c
│   │   └── command_parser.c
│   ├── tests/
│   │   └── testScript.c
│   └── utils/
│       └── file_io.c
├── include/
│   ├── ssd.h
│   ├── commands.h
│   ├── commands_parser.h
│   ├── tests.h
│   └── file_io.h
├── build/
│   └── Makefile
├── data/
│   ├── nand.txt
│   └── result.txt
└── scripts/
    └── run_tests.sh
