#ifndef MY_PARSE_H
#define MY_PARSE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char* filePath;
    size_t maxWidth;
    size_t maxHeight;
    double characterRatio;
    double edgeThreshold;
} args_t;

args_t parseArgs(int argc, char* argv[]);
#endif
