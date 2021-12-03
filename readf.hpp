#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

#ifdef __cplusplus
#define malloc(...) static_cast<char *>(malloc(__VA_ARGS__))
#define realloc(...) static_cast<char *>(realloc(__VA_ARGS__))
#endif

enum {
    READF_STR_BUFSIZE = 1
};

char * readf_str(char const * msg) {
    if(msg){
        fputs(msg, stdout);
        fflush(stdout);
    }
    int pos = 0;
    int buf_size = READF_STR_BUFSIZE;
    char * buf = malloc(READF_STR_BUFSIZE);
    if(buf == NULL) return NULL;
    int c;
	while(1){
        //grow buffer
        if(pos == buf_size){
            buf_size *= 2;
            char * tmp = realloc(buf, buf_size);
            if(tmp == NULL) goto error;
            buf = tmp;
        }
		c = fgetc(stdin);
		if(c == '\n'){//end of line/input
            buf[pos++] = '\0';
			break;
        }else if(c == EOF){//either an error or end of input
            if(!ferror(stdin)){//not an error
                buf[pos++] = '\0';
                break;
            }else goto error;
        }else{
            buf[pos++] = c;
        }
    }
    //shrink buf to used size
    char * tmp = realloc(buf, pos);
    if(tmp == NULL) goto error;
    buf = tmp;
    
    return buf;
error:
    free(buf);
    return NULL;
}

char readf_char(char const * msg) {
    while(true){
        if(msg){
            fputs(msg, stdout);
            fflush(stdout);
        }
        char val;
        int result = scanf(" %c", &val);
        if(result == 0 || result == EOF || getchar() != '\n'){
            while(getchar() != '\n');
            continue;
        }
        return val;
    }
}

long long readf_int(char const * msg, long long min, long long max) {
    while(true){
        if(msg){
            fputs(msg, stdout);
            fflush(stdout);
        }
        long long num = min;
        int result = scanf("%lld", &num);
        if(result == 0 || result == EOF || (num > max || num < min) || getchar() != '\n'){
            while(getchar() != '\n');
            continue;
        }
        return num;
    }
}

unsigned long long readf_uint(char const * msg, unsigned long long min, unsigned long long max) {
    while(true){
        if(msg){
            fputs(msg, stdout);
            fflush(stdout);
        }
        unsigned long long num = min;
        int result = scanf("%llu", &num);
        if(result == 0 || result == EOF || (num > max || num < min) || getchar() != '\n') {
            while(getchar() != '\n');
            continue;
        }
        return num;
    }
}

long double readf_float(char const * msg, long double min, long double max) {
    while(true){
        if(msg){
            fputs(msg, stdout);
            fflush(stdout);
        }
        long double num = min;
        int result = scanf("%Lf", &num);
        if(result == 0 || result == EOF || (num > max || num < min) || getchar() != '\n') {
            while(getchar() != '\n');
            continue;
        }
        return num;
    }
}

#ifdef __cplusplus
extern "C++" {
    static inline void readf(const char * msg, char * arg)
    { *arg = readf_char(msg); }
    static inline void readf(const char * msg, signed char * arg)
    { *arg = readf_int(msg, SCHAR_MIN, SCHAR_MAX); }
    static inline void readf(const char * msg, unsigned char * arg)
    { *arg = readf_uint(msg, 0, UCHAR_MAX); }
    static inline void readf(const char * msg, short * arg)
    { *arg = readf_int(msg, SHRT_MIN, SHRT_MAX); }
    static inline void readf(const char * msg, unsigned short * arg)
    { *arg = readf_uint(msg, 0, USHRT_MAX); }
    static inline void readf(const char * msg, int * arg)
    { *arg = readf_int(msg, INT_MIN, INT_MAX); }
    static inline void readf(const char * msg, unsigned * arg)
    { *arg = readf_uint(msg, 0, UINT_MAX); }
    static inline void readf(const char * msg, long * arg)
    { *arg = readf_int(msg, LONG_MIN, LONG_MAX); }
    static inline void readf(const char * msg, unsigned long * arg)
    { *arg = readf_uint(msg, 0, ULONG_MAX); }
    static inline void readf(const char * msg, long long * arg)
    { *arg = readf_int(msg, LLONG_MIN, LLONG_MAX); }
    static inline void readf(const char * msg, unsigned long long * arg)
    { *arg = readf_uint(msg, 0, ULLONG_MAX); }
    static inline void readf(const char * msg, float * arg)
    { *arg = readf_float(msg, -FLT_MAX, FLT_MAX); }
    static inline void readf(const char * msg, double * arg)
    { *arg = readf_float(msg, -DBL_MAX, DBL_MAX); }
    static inline void readf(const char * msg, long double * arg)
    { *arg = readf_float(msg, -LDBL_MAX, LDBL_MAX); }
    static inline void readf(const char * msg, char* * arg)
    { *arg = readf_str(msg); }
}
#else
#define readf(msg, X_ptr) do {\
*(X_ptr) = _Generic(*(X_ptr),\
    char: readf_char(msg),\
    signed char: readf_int(msg, SCHAR_MIN, SCHAR_MAX),\
    unsigned char: readf_uint(msg, 0, UCHAR_MAX),\
    short: readf_int(msg, SHRT_MIN, SHRT_MAX),\
    unsigned short: readf_uint(msg, 0, USHRT_MAX),\
    int: readf_int(msg, INT_MIN, INT_MAX),\
    unsigned: readf_uint(msg, 0, UINT_MAX),\
    long: readf_int(msg, LONG_MIN, LONG_MAX),\
    unsigned long: readf_uint(msg, 0, ULONG_MAX),\
    long long: readf_int(msg, LLONG_MIN, LLONG_MAX),\
    unsigned long long: readf_uint(msg, 0, ULLONG_MAX),\
    float: readf_float(msg, -FLT_MAX, FLT_MAX),\
    double: readf_float(msg, -DBL_MAX, DBL_MAX),\
    long double: readf_float(msg, -LDBL_MAX, LDBL_MAX),\
    char*: readf_str(msg)\
);\
}while(0)
#endif

#ifdef __cplusplus
}
#undef malloc
#undef realloc
#endif

