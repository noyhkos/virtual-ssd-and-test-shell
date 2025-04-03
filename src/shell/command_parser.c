#include <stdio.h>
#include <string.h> // strtok, strcpy, strlen, memset
#include <ctype.h> //isdigit(), isxdigit()
#include <stdlib.h> // atoi()

#include "command_parser.h"

#define MAX_BUFFER_SIZE 256 // 커맨드라인 = 넉넉잡아 최대 256글자
#define MAX_TOKENS 4 // 커맨드 인자 개수 최대 3개 (넉넉잡아 4개)

static int is_valid_lba(const char *lba_str){
    if(lba_str == NULL || *lba_str == '\0')return 0;
    for(int i=0; lba_str[i] != '\0'; i++){
        if(!isdigit((unsigned char)lba_str[i]))return 0;
    }
    int lba = atoi(lba_str);
    return (lba >= 0 && lba <= 99);
}

static int is_valid_data(const char *data_str){
    if(data_str == NULL || *data_str == '\0')return 0;
    if(strlen(data_str) != 10) return 0;
    if(data_str[0]!='0' || data_str[1]!='x') return 0;
    for(int i=2; i<10; i++){
        if(!isxdigit((unsigned char)data_str[i]))return 0;
    }
    return 1;
}

// input=명령어 전체, result=결과 저장할 구조체 주소 
int parse_command(const char *input, ParsedCommand *result){
    // argument가 들어오지 않으면 실패
    if(input == NULL || result == NULL)return -1;

    // 들어온 커맨드라인 버퍼에 복사 
    //  => strtok는 문자열에 '\0'를 삽입하는 방식이라
    //     원본 회손을 방지하기 위해 복사본 생성성
    char buffer[MAX_BUFFER_SIZE];
    strncpy(buffer, input, MAX_BUFFER_SIZE-1);
    buffer[MAX_BUFFER_SIZE-1] = '\0';

    // 토큰 분리
    char *tokens[MAX_TOKENS];
    int token_count = 0;
    char *token =strtok(buffer, " \0\n");
    while(token != NULL && token_count<MAX_TOKENS){
        tokens[token_count++] = token;
        token = strtok(NULL, " \0\n");
    }

    //예외처리 (빈 입력)
    if(token_count == 0) return -1;

    // result 구조체 초기입력(초기화)
    result->type = CMD_UNKNOWN;
    result->lba = -1;
    memset(result->data, 0, sizeof(result->data));

    //명령어(인자[0])에 따라 result에 값 저장
    // write
    if(strcmp(tokens[0],"write")==0){
        //인자 개수 부족하면 컷
        if(token_count!=3)return -1;
        if(!is_valid_lab(tokens[1]) || !is_valid_data(tokens[2]))return -1;
        result->type = CMD_WRITE;
        result->lba = atoi(tokens[1]);
        strcpy(result->data, tokens[2], sizeof(result->data) -1);
    } 
    // read
    else if(strcmp(tokens[0],"read")==0){
        if(token_count!=2)return -1;
        if(!is_valid_lab(tokens[1]))return -1;
        result->type = CMD_READ;
        result->lba = atoi(tokens[1]);
    } 
    // exit
    else if(strcmp(tokens[0],"exit")==0){
        if(token_count!=1)return -1;
        result->type = CMD_EXIT;
    } 
    // help
    else if(strcmp(tokens[0],"help")==0){
        if(token_count!=1)return -1;
        result->type = CMD_HELP;
    } 
    // fullwrite
    else if(strcmp(tokens[0],"fullwrite")==0){
        if(token_count!=2)return -1;
        if(!is_valid_data(tokens[1]))return -1;
        result->type = CMD_FULLWRITE;
        strcpy(result->data, tokens[1], sizeof(result->data));
    } 
    // fullread
    else if(strcmp(tokens[0],"fullread")==0){
        if(token_count!=1)return -1;
        result->type = CMD_FULLREAD;
    } 
    // testapp1
    else if(strcmp(tokens[0],"testapp1")==0){
        if(token_count!=1)return -1;
        result->type = CMD_TESTAPP1;
    } 
    // testapp2
    else if(strcmp(tokens[0],"testapp2")==0){
        if(token_count!=1)return -1;
        result->type = CMD_TESTAPP2;
    } 
    // none
    else {
        result->type = CMD_UNKNOWN;
        return -1;
    }

    return 0;
}