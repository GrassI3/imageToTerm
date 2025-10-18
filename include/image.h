#ifndef MY_IMAGE_H
#define MY_IMAGE_H

typedef struct{
    size_t width;
    size_t height;
    size_t channels;
    double* data;
} image_t;

image_t loadImage(char* filePath);
void freeImage(image_t* img);

image_t resizeImage(image_t* ori, size_t maxWidth, size_t maxHeight, double character_ratio);
image_t grayscale(image_t* ori);

double* getPixel(image_t* img, size_t x, size_t y);
void setPixel(image_t* img, size_t x, size_t y, double* new_pixel);

void getConvolution(image_t* img, double* kernel, double* out);
void getSobel(image_t* img, double* out_x, double* out_y);

#endif
