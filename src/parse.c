#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <sys/ioctl.h>
#endif

#define DEFAULT_MAX_WIDTH 64
#define DEFAULT_MAX_HEIGHT 48
#include "../include/parse.h"


int terminalSize(int* width, int* height){
    struct winsize ws;
    if(!isatty(0)){
        return 0;
    }
    if (ioctl(0, TIOCGWINSZ, &ws) == 0){
        *width = (size_t) ws.ws_col;
        *height = (size_t) ws.ws_row;
        return 1;
    }
    return 0;
}

args_t parseArgs(int argc, char* argv[]){
    args_t args;
    args.filePath = NULL;
    args.maxWidth = DEFAULT_MAX_WIDTH;
    args.maxHeight = DEFAULT_MAX_HEIGHT;

    terminalSize(&args.maxWidth, &args.maxHeight);

    args.filePath = argv[1];
    return args
}





