#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#pragma GCC diagnostic pop

#include "../include/image.h"

image_t loadImage(char* filePath){
    int width, height, channels;
    //loading image
    unsigned char* rawData = stbi_load(filePath, &width, &height, &channels, 0);
    //error handling if image cannot load
    if(!rawData){
        fprintf(stderr, "Error: Failed to load image '%s': %s!\n", filePath, stbi_failure_reason());
        return (image_t){0};
    }
    //allocating memory for image data
    size_t dataSize = (size_t)(width * height * channels);
    double* data = (double*)malloc(dataSize * sizeof(double));
    //error handling if memory allocation fails
    if(!data){
        fprintf(stderr, "Error: Failed to allocate memory for image data!\n");
        stbi_image_free(rawData);
        return (image_t){0};
    }
    //doing some ascii art magic
    for(size_t i = 0; i < dataSize; i++){
        data[i] = rawData[i]/255.0;
    }
    //freeing raw image data and return
    stbi_image_free(rawData);
    return (image_t){.data = (size_t)data, .width = (size_t)width, .height = (size_t)height, .channels = (size_t)channels};
}


void freeImage(image_t* img){
    if(img && img->data){
        free(img->data);
        img->data = NULL;
        img->width = img->height = img->channels = 0;
    }
}

// Gets the pointer to pixel data at index (x, y)
double* getPixel(image_t* img, size_t x, size_t y){
    return &img->data[(y * img->width + x) * img->channels];
}

// Sets pixel channel values to those of new_pixel
void setPixel(image_t* img, size_t x, size_t y, double* new_pixel){
    double* pixel =getPixel(img, x, y);
    for(size_t c = 0; c < img->channels; c++){
        pixel[c] = new_pixel[c];
    }
}

void getAverageColor(image_t* img, double* avg, size_t x1, size_t x2, size_t y1, size_t y2 ){
    for (size_t c = 0; c < img->channels; c++){
        avg[c] = 0.0;
    }
    //get avg
    for (size_t y=y1; y < y2; y++){
        for (size_t x=x1; x < x2; x++){
            double* pixel = getPixel(img, x, y);
            for (size_t c = 0; c < img->channels; c++){
                avg[c] += pixel[c];
            }
        }
    }

    // Divide by number of pixels in region
    double numPixels = (double)((x2 - x1) * (y2 - y1));
    for (size_t c = 0; c < img->channels; c++){
        avg[c] /= numPixels;
    }
}

image_t resizeImage(image_t* ori, size_t maxWidth, size_t maxHeight, double character_ratio){
    size_t width, height;
    size_t channels = ori->channels;

    //Dividing heights by 2 for approximate terminal font aspect ratio
    size_t proposed_height = (ori->height * maxWidth) / (character_ratio * ori->width);
    if (proposed_height <= maxHeight) {
        width = maxWidth, height = proposed_height;
    } else {
        width = (character_ratio * ori->width * maxHeight) / (ori->height);
        height = maxHeight;
    }

    double* data = (double*)malloc(width * height * channels * sizeof(double));
    if(!data){
        fprintf(stderr, "Error: Failed to allocate memory for resized image data!\n");
        return (image_t){0};
    }

    for(size_t j=0; j<height; j++){
        size_t y1 = (j * ori->height) / height;
        size_t y2 = ((j + 1) * ori->height) / height;
        for(size_t i=0; i<width; i++){
            size_t x1 = (i * ori->width) / width;
            size_t x2 = ((i + 1) * ori->width) / width;
            double* pixel = &data[(j * width + i) * channels];
            getAverageColor(ori, pixel, x1, x2, y1, y2);
        }
    }
    return (image_t){.data = data, .width = width, .height = height, .channels = channels};
}


image_t grayscale(image_t* ori){
    size_t width = ori->width;
    size_t height = ori->height;
    size_t channels = 1;

    double* data = (double*)malloc(width * height * channels * sizeof(double));
    if(!data){
        fprintf(stderr, "Error: Failed to allocate memory for grayscale image data!\n");
        return (image_t){0};
    }
    image_t new_img = {.data = data, .width = width, .height = height, .channels = channels};   
    for(size_t j=0; j<height; j++){
        for(size_t i=0; i<width; i++){
            double* pixel = getPixel(ori, i, j);
            double grayscale = 0.2126 * pixel[0] + 0.7152 * pixel[1] + 0.0722 * pixel[2];
            setPixel(&new_img, i, j, &grayscale);
        }
    }
    return new_img;
}

double calculate_convolution_value(image_t* image, double* kernel, size_t x, size_t y, size_t c) {
    double result = 0.0;
    for (int j = -1; j < 2; j++) {
        for (int i = -1; i < 2; i++) {
            size_t image_index = c + ((x + i) + (y + j) * image->width) * image->channels;
            size_t kernel_index = (i + 1) + (j + 1) * 3;

            result += kernel[kernel_index] * image->data[image_index];
        }
    }
    return result;
}


void getConvolution(image_t* img, double* kernel, double* out){
    size_t width = img->width;
    size_t height = img->height;
    size_t channels = img->channels;

    for(size_t y = 1; y < height - 1; y++){
        for(size_t x = 1; x < width - 1; x++){
            for(size_t c = 0; c < channels; c++){
                size_t out_index = c + (x + y * width) * channels;
                out[out_index] = calculate_convolution_value(img, kernel, x, y, c);
            }
        }
    }
}

void setSobel(image_t* img, double* out_x, double* out_y){
    double sobel_x[9] = {
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    };
    double sobel_y[9] = {
         1,  2,  1,
         0,  0,  0,
        -1, -2, -1
    };
    getConvolution(img, sobel_x, out_x);
    getConvolution(img, sobel_y, out_y);
}