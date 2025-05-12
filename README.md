# Virtual SSD and Test Shell

[가상 SSD와 테스트를 위한 커스텀 쉘 개발 프로젝트]

1. 구조
- 운영체제: ubuntu 20.04
- 언어: C(gcc), shell script(bash)
- Project directory: ~/ssdTest/
- 필수 포함 파일: ssd.c, TestShell.c, nand.txt, result.txt, testScript
- 설명:  
    - 가상 ssd 프로그램은 파일 입출력을 실행한다.
    - TestShell을 이용해 ssd에 여러가지 명령을 보낼 수 있다.
    - ssd는 nand.txt와 result.txt에 결과를 저장하는 단순한 업무만 수행한다.

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
      a) 0~5번 lba에 0xAAAABBBB write 30번 씩 수행
      b) 0~5번 lba에 0x12345678 write
      c) 0~5번 read 후 값이 잘 입력되었는지 확인
      d) test결과 출력

3. 주안점
    1) 파일 입출력 과정에서의 문자열 Parsing
    2) Structure와 Union을 활용한 Binary데이터 관리
    3) 2)를 통한 Byte/Bit 단위 Parsing
    4) Divided Compile을 통한 팀 프로젝트 관리
    5) 협업을 위한 효율적인 Source File - Header File 구조 생성
    6) 리눅스에서의 C프로그램 컴파일 및 Build를 위한 shell script - Makefile의 활용


프로젝트 구조:
~/ssdTest/
├── testShell.exe
├── bin/
│   └── ssd.exe
├── src/                    
│   ├── ssd/               
│   │   ├── ssd.c            // Team A: Logical Block 처리 및 핵심 기능 구현
│   │   └── ssd_api.c        // Team A: SSD 관련 API 모듈
│   ├── shell/              
│   │   ├── TestShell.c     // Team B: 사용자 셸 인터페이스 구현
│   │   ├── command.c        // Team B: 셸 명령어 
│   │   └── command_parser.c // Team B: 명령어 파싱 및 포맷 체크 로직
│   ├── tests/              
│   │   └── testScript.c   // Team C: 테스트 스크립트 (testapp1, testapp2 등)
│   └── utils/              
│       └─ file_io.c        // Team A: 파일 입출력 및 문자열 파싱 유틸리티
├── include/                
│   ├── ssd.h                // Team A: SSD 모듈 인터페이스 정의
│   ├── commands.h            // Team B: 셸 명령어 관련 상수 및 함수 프로토타입
│   ├── commands_parser.h     // Team B: 명령어 파싱 관련 정의
│   ├── tests.h              // Team C: 테스트 관련 정의
│   └── file_io.h            // Team A: 파일 입출력 유틸리티 헤더
├── build/                  
│   └── Makefile             // Team C: 전체 프로젝트 빌드 관리
├── data/                   
│   ├── nand.txt            // 가상 NAND 저장공간 (공용, 초기화 및 관리)
│   └── result.txt          // 읽기 결과 저장 파일 (공용)
└── scripts/                
    └── run_tests.sh         // Team C: 자동 테스트 실행 스크립트
