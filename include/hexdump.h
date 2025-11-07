#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BYTES_PER_LINE 16

static int is_printable(unsigned char c){
    return c >= 0x20 && c <= 0x7E;
}

static void print_line(size_t offset, const unsigned char* buff, size_t n){
    /* offset (print as size_t) */
#if defined(_MSC_VER)
    /* MSVC doesn't support %z, use unsigned long long for portability */
    printf("%08llx  ", (unsigned long long)offset);
#else
    printf("%08zx  ", offset);
#endif

    /* hex bytes */
    for(size_t i = 0; i < BYTES_PER_LINE; ++i){
        if(i < n){
            printf("%02x", (unsigned)buff[i]);
        } else {
            printf("  ");
        }
        if(i != BYTES_PER_LINE - 1) putchar(' ');
        if(i == 7) putchar(' '); /* extra gap after 8 bytes */
    }

    /* ASCII view */
    printf(" |");
    for(size_t i = 0; i < n && i < BYTES_PER_LINE; ++i){
        unsigned char c = buff[i];
        putchar(is_printable(c) ? c : '.');
    }
    printf("|\n");
}