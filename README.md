# Virtual SSD and Test Shell

**[가상 SSD와 테스트를 위한 커스텀 쉘 개발 프로젝트]**

## 1. 구조

- **운영체제**: Ubuntu 20.04  
- **언어**: C (gcc), Shell Script (bash)  
- **프로젝트 디렉토리**: `~/ssdTest/`  
- **필수 파일**: `ssd.c`, `TestShell.c`, `nand.txt`, `result.txt`, `testScript`

### 설명

- 가상 SSD 프로그램은 파일 입출력을 실행한다.
- TestShell을 이용해 SSD에 여러 가지 명령을 보낼 수 있다.
- SSD는 `nand.txt`와 `result.txt`에 결과를 저장하는 단순한 작업을 수행한다.

2. 기능별 설명
  1) ssd.c
    - 4Byte 단위 Logical Block
    - 0~99번 총 100개의 Logical Block을 갖는다(400Byte)
    - Read, Write 명령 단 두개만 존재. 추가 기능 생성을 위한 여지 확보
    - "W" 명령어 (ex: "ssd W 33(LBA) 0x12345678") => nand.txt 33번 영역에 0x12345678(4Byte) 저장
    - "R" 명령어 (ex: "ssd R 33(LBA)") => nand.txt에서 33번 영역 데이터를 읽고, result.txt 에 저장
    - 인자: LBA=10진수, value=16진수(0x와 16지수 숫자 8자리를 포함하여 총 10글자)
  2) nand.txt
    - 4Byte x 100개 총 400Byte 저장공간 확보 필
    - 처음에 모든 bit가 0으로 초기화
  3) result.txt
    - R 명령으로 반환된 4Byte데이터 저장공간
    - 새로운 R 명령이 호출될 때마다 초기화
  4) TestShell.c
    - write, read, exit, help, fullwrite, fullread 명령 수행
    - write [LBA] [4Byte Data("0x00000000")] => ssd 프로그램 호출
    - read [LBA]: ssd호출 후 result.txt에 저장된 값 가져와 화면에 출력
    - exit : 쉘 탈출
    - help 명령어 사용법 출력
    - fullwrite [data] : nand.txt 모든 L.B.에 "data" 입력
    - fullread: nand.txt 모두 화면에 출력
    - testapp1: (후술)
    - testapp2: (후술)
    - 없는 명령어: "INALID COMMAND" 출력. segmentation fault 절대 금지.
    - ssd 파라미터 format check 필(엄격)
    - LBA: 0~99 십진수(숫자)
    - DATA: 0x[0~9, A~F] 8자리
  5) testScript.c
    - testShell 내부에서 활용될 api 함수
    - testapp1, testapp2 명령어 수행
    - testapp1:
      a) fullwirte(임의의 값 ex)"0x1234ABCD") 수행
      b) fullread 하면서 ssd 정상작동 여부확인
      c) test결과 출력
    - testapp2:
      a) 0~10번 lba에 0xAAAABBBB write 50번 씩 수행
      b) 0~10번 lba에 0x12345678 write
      c) 0~10번 read 후 값이 잘 입력되었는지 확인
      d) test결과 출력


```
프로젝트 구조:
├── ssd/ 
│   ├── src/
│   │   ├── ssd.c
│   │   ├── cmd_read.c
│   │   ├── cmd_write.c
│   ├── includes/
│   │   ├── ssd_common.h
│   │   ├── nand_cmd.h
│   ├── data/
│   │   ├── nand.txt             # 400-byte SSD storage (100 blocks x 4 bytes)
│   │   ├── result.txt           # read result storage (4 bytes)
│   ├── Makefile
│   └── ssd

├── driver/
│   ├── src/
│   │   ├── main.c
│   │   ├── driver_write.c
│   │   ├── driver_read.c
│   │   ├── driver_fullwrite.c 
│   │   ├── driver_fullread.c 
│   │   ├── testApp.c
│   ├── includes/
│   │   ├── driver_common.h
│   │   ├── driver_command.h
│   ├── Makefile
│   └── driver                   # 실행파일 (빌드시 생성)
```
