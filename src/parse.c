#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/parse.h"

#define DEFAULT_MAX_WIDTH 64
#define DEFAULT_MAX_HEIGHT 48
#define DEFAULT_CHARACTER_RATIO 2.0
#define DEFAULT_EDGE_THRESHOLD 4.0


void print_help(char* exec_alias) {
    printf("USAGE:\n");
    printf("\t%s <path/to/image> [OPTIONS]\n\n", exec_alias);

    printf("ARGUMENTS:\n");
    printf("\t<path/to/image>\t\tPath to image file\n\n");

    printf("OPTIONS:\n");
    printf("\t-mw <width>\t\tMaximum width in characters (default: terminal width OR %d)\n", DEFAULT_MAX_WIDTH);
    printf("\t-mh <height>\t\tMaximum height in characters (default: terminal height OR %d)\n", DEFAULT_MAX_HEIGHT);
    printf("\t-et <threshold>\t\tEdge detection threshold, range: 0.0 - 4.0 (default: %.1f, disabled)\n", DEFAULT_EDGE_THRESHOLD);
    printf("\t-cr <ratio>\t\tHeight-to-width ratio for characters (default: %.1f)\n", DEFAULT_CHARACTER_RATIO);
}


// Get size of terminal in characters. Returns 1 if successful.
int try_get_terminal_size(size_t* width, size_t* height) {
    struct winsize ws;

    // Abort if not terminal
    if (!isatty(0))
        return 0;
    
    if (ioctl(0, TIOCGWINSZ, &ws) == 0) {
        *width = (size_t) ws.ws_col;
        *height = (size_t) ws.ws_row;
        return 1;
    }

    return 0;
}


args_t parseArgs(int argc, char* argv[]) {
    // Get variable defaults
    args_t args = {
        .filePath = NULL,
        .maxWidth = DEFAULT_MAX_WIDTH,
        .maxHeight = DEFAULT_MAX_HEIGHT,
        .characterRatio = DEFAULT_CHARACTER_RATIO,
        .edgeThreshold = DEFAULT_EDGE_THRESHOLD,
    };

    try_get_terminal_size(&args.maxWidth, &args.maxHeight);

    // If no file given
    if (argc == 1) {
        print_help(argv[0]);
        return args;
    }

    // Get file path
    if (!strcmp(argv[1], "-h")) {
        print_help(argv[0]);
        return args;
    } else {
        args.filePath = argv[1];
    }

    // Get optional parameters
    for (size_t i = 2; i < (size_t) argc; i++) {
        if (!strcmp(argv[i], "-mw") && i + 1 < (size_t) argc)
            args.maxWidth = (size_t) atoi(argv[++i]);
        else if (!strcmp(argv[i], "-mh") && i + 1 < (size_t) argc)
            args.maxHeight = (size_t) atoi(argv[++i]);
        else if (!strcmp(argv[i], "-et") && i + 1 < (size_t) argc)
            args.edgeThreshold = atof(argv[++i]);
        else if (!strcmp(argv[i], "-cr") && i + 1 < (size_t) argc)
            args.characterRatio = atof(argv[++i]);
        else 
            fprintf(stderr, "Warning: Ignoring invalid or incomplete argument '%s'\n", argv[i]);
    }

    return args;
}
