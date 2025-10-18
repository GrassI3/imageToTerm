#include<stdio.h>
#include<stdlib.h>
#include "../include/image.h"
#include "../include/parse.h"
#include "../include/print.h"
#include "../include/stb_image.h"

int main(int argc, char* argv[]){

    args_t args = parseArgs(argc, argv);
    if (args.filePath == NULL) return 1;

    //loading the image
    image_t original = loadImage(args.filePath);
    if (!original.data) return 1;

    //resize image
    image_t resized = resizeImage(&original, args.maxWidth, args.maxHeight, args.characterRatio);
    if(!resized.data){
        freeImage(&original);
        return 1;
    }

    //print iamge
    printImage(&resized, args.edgeThreshold);
    freeImage(&original);
    freeImage(&resized);
}