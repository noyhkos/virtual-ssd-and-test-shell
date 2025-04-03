~/ssdTest/
├── src/                    
│   ├── core/               
│   │   ├── ssd.c            // Team A: Logical Block 처리 및 핵심 기능 구현
│   │   └── ssd_api.c        // Team A: SSD 관련 API 모듈
│   ├── shell/              
│   │   ├── TestShell.c     // Team B: 사용자 셸 인터페이스 구현
│   │   └── command_parser.c & command_parser.h// Team B: 명령어 파싱 및 포맷 체크 로직
│   ├── tests/              
│   │   ├── testScript.c   // Team C: 테스트 스크립트 (testapp1, testapp2 등)
│   │   └── test_utils.c   // Team C: 테스트 유틸리티 및 데이터 검증 함수
│   └── utils/              
│       ├── file_io.c        // Team A: 파일 입출력 및 문자열 파싱 유틸리티
│       └── file_io.h        // Team A: 파일 입출력 유틸리티 헤더
├── include/                
│   ├── ssd.h                // Team A: SSD 모듈 인터페이스 정의
│   ├── commands.h            // Team B: 셸 명령어 관련 상수 및 함수 프로토타입
│   └── tests.h              // Team C: 테스트 관련 정의
├── build/                  
│   ├── Makefile             // Team C: 전체 프로젝트 빌드 관리
│   └── build.sh             // Team C: 빌드 및 배포 자동화 스크립트
├── data/                   
│   ├── nand.txt            // 가상 NAND 저장공간 (공용, 초기화 및 관리)
│   └── result.txt          // 읽기 결과 저장 파일 (공용)
├── docs/                   
│   ├── README.md            // Team C: 프로젝트 개요 및 사용법 문서
│   ├── design_spec.md       // Team C: 상세 설계 및 모듈 간 인터페이스 문서
│   └── team_roles.md        // Team C: 팀원 역할 및 업무 분담 문서
└── scripts/                
    └── run_tests.sh         // Team C: 자동 테스트 실행 스크립트
