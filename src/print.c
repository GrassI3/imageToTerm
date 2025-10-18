#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "../include/image.h"
#include "../include/print.h"

// valid printing characters
#define VALID_CHARS " .-=+*x#$&X@"
#define NUM_VALID_CHARS (sizeof(VALID_CHARS) - 1)

// Color ANSI codes
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1b[0m"

typedef struct{
    float hue;
    float saturation;
    float value;
} hsv_t;

double* getMax(double* a, double* b, double* c){
    if(*a >= *b && *a >= *c) return a;
    else if(*b >= *a && *b >= *c) return b;
    else return c;
}

double* getMin(double* a, double* b, double* c){
    if(*a <= *b && *a <= *c) return a;
    else if(*b <= *a && *b <= *c) return b;
    else return c;
}

hsv_t rgbToHsv(double red, double green, double blue){
    hsv_t hsv;
    double* cMax = getMax(&red, &green, &blue);
    double* cMin = getMin(&red, &green, &blue);
    
    hsv.value = *cMax;
    double chroma = *cMax - *cMin;

    // calculate saturation
    if( fabs(hsv.value) < 1e-6 ) hsv.saturation = 0.0;
    else hsv.saturation = chroma / hsv.value;

    // calculate hue
    if( fabs(chroma) < 1e-4 ) hsv.hue = 0.0;
    else if (cMax == &red) hsv.hue = 60.0 * fmod((green - blue) / chroma, 6.0);
    else if (cMax == &green) hsv.hue = 60.0 * (2.0 + (blue - red) / chroma);
    else hsv.hue = 60.0 * (4.0 + (red - green) / chroma);

    return hsv;
}

char* getColourCode(const hsv_t* hsv){
    if(hsv->saturation<0.25) return WHT;
    if(hsv->hue>=30.0 && hsv->hue<90.0) return YEL;
    else if(hsv->hue>=90.0 && hsv->hue<150.0) return GRN;
    else if(hsv->hue>=150.0 && hsv->hue<210.0) return CYN;
    else if(hsv->hue>=210.0 && hsv->hue<270.0) return BLU;
    else if(hsv->hue>=270.0 && hsv->hue<330.0) return MAG;
    else return RED;
}

char getAsciiChar(double grayscale){
    size_t idx = (size_t)(grayscale * NUM_VALID_CHARS);
    if (idx >= NUM_VALID_CHARS) idx = NUM_VALID_CHARS - 1;
    return VALID_CHARS[idx];
}

char getSobelChar(double sobelAngle){
    if ((22.5 <= sobelAngle && sobelAngle <= 67.5) || (-157.5 <= sobelAngle && sobelAngle <= -112.5)) return '\\';
    else if ((67.5 <= sobelAngle && sobelAngle <= 112.5) || (-112.5 <= sobelAngle && sobelAngle <= -67.5)) return '_';
    else if ((112.5 <= sobelAngle && sobelAngle <= 157.5) || (-67.5 <= sobelAngle && sobelAngle <= -22.5)) return '/';
    else return '|';
}

void printImage(image_t* img, double edgeThreshold){
}