#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifdef _WIN32
    #include <io.h>
    #include <windows.h>
    #define isatty _isatty
    #define fileno _fileno
#else
    #include <unistd.h>
#endif

#define COL_PRINTABLE   "\x1b[32m"  /* green  */
#define COL_NONPRINT    "\x1b[90m"  /* gray   */
#define COL_RESET       "\x1b[0m"


#define BYTES_PER_LINE 16

static int is_printable(unsigned char c){
    return c >= 0x20 && c <= 0x7E;
}

static void print_line(size_t offset, const unsigned char* buff, size_t n,size_t width, int show_ascii){
    /* offset (print as size_t) */
#if defined(_MSC_VER)
    /* MSVC doesn't support %z, use unsigned long long for portability */
    printf("%08llx  ", (unsigned long long)offset);
#else
    printf("%08zx  ", offset);
#endif

    /* hex bytes */
    size_t half=width/2;
    for(size_t i=0;i<width;i++){
        if(i<n){
            if (is_printable(buff[i])) fputs(COL_PRINTABLE, stdout);
            else fputs(COL_NONPRINT, stdout);
            printf("%02X", (unsigned)buff[i]);
            fputs(COL_RESET, stdout);
        }
        else  printf(" ");
        if(i==half-1){
            printf("  ");
        }
        else printf(" ");
    }

    /* ASCII view */
    if(show_ascii)
    {
        printf(" |");
        for(size_t i = 0; i < n && i < BYTES_PER_LINE; ++i){
            unsigned char c = buff[i];
            if(is_printable(c)){
                fputs(COL_PRINTABLE, stdout);
            }
            else{
                fputs(COL_NONPRINT, stdout);
            }
            putchar(is_printable(c) ? (char)c : '.');
        }
        fputs(COL_RESET, stdout);
        printf("|\n");
    }
}