# Virtual SSD and Test Shell

**가상 SSD와 테스트를 위한 커스텀 셸 개발 프로젝트**

---

## 1. 프로젝트 개요

- **운영체제**: Ubuntu 20.04  
- **언어**: C (gcc), Shell Script (bash)  
- **디렉토리**: `~/ssdTest/`  
- **핵심 파일**: `ssd.c`, `TestShell.c`, `nand.txt`, `result.txt`, `testScript`

---

## 2. 프로젝트 설명

- 가상 SSD 프로그램은 파일 입출력을 통해 `nand.txt`와 `result.txt`를 조작한다.
- TestShell을 통해 사용자가 SSD에 명령을 보내고 결과를 확인할 수 있다.
- SSD는 매우 단순한 구조로 구성되어 있어 C 기반 입출력 학습에 적합하다.

---

## 3. 주요 기능

### 🔹 3.1. `ssd.c`

- 4Byte 단위 Logical Block
- LBA 0~99 총 100개 (총 400Byte)
- 명령어:
  - `W` (Write): `ssd W 33 0x12345678` → 33번 영역에 0x12345678 저장
  - `R` (Read) : `ssd R 33` → 33번 영역 값 result.txt에 저장
- **입력 인자**:  
  - `LBA`: 0~99 (10진수)  
  - `DATA`: 0x로 시작하는 8자리 16진수 (예: `0x1234ABCD`)

---

### 🔹 3.2. `nand.txt`

- SSD 저장 공간 (100개의 4Byte 블록 = 400Byte)
- 초기값: 모든 bit 0

### 🔹 3.3. `result.txt`

- R 명령 결과값 저장 (4Byte)
- 새로운 R 명령마다 초기화됨

---

### 🔹 3.4. `driver.c`

- 사용자가 직접 명령어 입력 (커맨드 셸 역할)
- 지원 명령어:
  - `write [LBA] [0xDATA]`  
  - `read [LBA]`
  - `fullwrite [0xDATA]`
  - `fullread`
  - `help`
  - `exit`
  - `testapp1`
  - `testapp2`
- 기타:
  - 존재하지 않는 명령어: `"INVALID COMMAND"` 출력
  - 입력 포맷 검사 엄격
  - **Segmentation Fault 절대 금지**

---

### 🔹 3.5. `testApp.c`

- 셸 내부에서 자동 테스트 수행용 API 제공

#### 📌 `testapp1`

1. 전체 영역 `0x1234ABCD`로 `fullwrite`  
2. `fullread` 결과 확인  
3. 성공 여부 출력

#### 📌 `testapp2`

1. LBA 0~10에 `0xAAAABBBB` 50번씩 write  
2. 동일 위치에 `0x12345678` write  
3. read로 결과 확인 후 일치 여부 판단  
4. 성공 여부 출력

---

## 4. 프로젝트 디렉토리 구조
```
virtual-ssd-driver/
├── ssd/
│ ├── src/
│ │ ├── ssd.c
│ │ ├── cmd_read.c
│ │ ├── cmd_write.c
│ ├── includes/
│ │ ├── ssd_common.h
│ │ ├── nand_cmd.h
│ ├── data/
│ │ ├── nand.txt # 100 blocks x 4 bytes
│ │ ├── result.txt # latest read result
│ ├── Makefile
│ └── ssd # 실행파일

├── driver/
│ ├── src/
│ │ ├── main.c
│ │ ├── driver_write.c
│ │ ├── driver_read.c
│ │ ├── driver_fullwrite.c
│ │ ├── driver_fullread.c
│ │ ├── testApp.c
│ ├── includes/
│ │ ├── driver_common.h
│ │ ├── driver_command.h
│ ├── Makefile
│ └── driver # 실행파일
```

---

## 5. 빌드 방법

```
bash
# SSD 빌드
cd ssd
make

# Driver 빌드
cd ../driver
make
```
