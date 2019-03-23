#include "statistics.h"
#include "image.h"

//
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#define CHANNEL_NUM 3
//

aek_image aek_imread(char *filename){
    int w, h, c;
    unsigned char* data=stbi_load(filename,&w,&h,&c,3);
    if(!data){
        fprintf(stderr,"Cannot load image \"%s\"\n STB Reason: %s\n",
                        filename,stbi_failure_reason());
        exit(0);
    }
    aek_image img;
    img.w=w;
    img.h=h;
    img.c=c;
    img.data=data;
    return img;
}

void aek_imwrite_png(aek_image img, const char *name){
    int success=0;
    if(img.c==1){
        img=aek_Gray_to_RGB(img);
    }
    success=stbi_write_png(name,img.w,img.h,img.c,img.data,img.c*img.w);
    if(!success){
        fprintf(stderr, "Failed to write image %s\n",name);
    }
}

aek_image aek_RGB_to_Gray(aek_image img){
    aek_image gray;
    gray.w=img.w;
    gray.h=img.h;
    gray.c=1;
    gray.data=malloc(gray.w*gray.h);

    int index;
    unsigned char r,g,b;
    for(int i = 0; i < gray.h; i++)
    {   
        for(int j = 0; j < gray.w; j++)
        {
            index=i*gray.w+j;
            r=img.data[index*3+0];
            g=img.data[index*3+1];
            b=img.data[index*3+2];
            gray.data[index]=0.2126*r+0.7152*g+0.0722*b;
        }        
    }
    return gray;
}

aek_image aek_Gray_to_RGB(aek_image img){
    aek_image RGB;
    RGB.w=img.w;
    RGB.h=img.h;
    RGB.c=3;
    RGB.data=malloc(RGB.w*RGB.h*RGB.c);

    int index;
    for(int i = 0; i < RGB.h; i++)
    {
        for(int j=0;j<RGB.w;j++){
            index=i*RGB.w+j;
            RGB.data[index*3+0]=img.data[index];
            RGB.data[index*3+1]=img.data[index];
            RGB.data[index*3+2]=img.data[index];
        }
    }
    return RGB;
}

void aek_setpixel3b(aek_image img,int x,int y,unsigned char r,unsigned char g,unsigned char b){
    int index=y*img.w+x;
    if(img.c==1){
        img.data[index]=r;
    }
    else
    {
        img.data[index*3+0]=r;
        img.data[index*3+1]=g;
        img.data[index*3+2]=b;
    }    
}

void aek_setpixel(aek_image img,int x,int y,aek_color color){
    int index=y*img.w+x;
    if(img.c==1){
        img.data[index]=color.r;
    }
    else
    {
        img.data[index*3+0]=color.r;
        img.data[index*3+1]=color.g;
        img.data[index*3+2]=color.b;
    } 
}

int* aek_histogram(aek_image img){
    int* Histogram = malloc(256*sizeof(int));
	for (int i = 0; i < 256; i++) {
		Histogram[i] = 0;
	}
	for (int i = 0; i < img.h; i++) {
		for (int j = 0; j < img.w; j++) {
			Histogram[img.data[i*img.w + j]]++;
		}
	}
	return Histogram;
}

uint8_t* RGB_to_Gray(uint8_t* rgb_image, int width, int height){
    uint8_t* gray_image;
    gray_image=malloc(width*height);
    uint8_t r,g,b;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            r=rgb_image[(i*width+j)*3+0];
            g=rgb_image[(i*width+j)*3+1];
            b=rgb_image[(i*width+j)*3+2];
            gray_image[i*width+j]=0.2126*r+0.7152*g+0.0722*b;
        }
    }
    return gray_image;
}

uint8_t* Gray_to_RGB(uint8_t* gray_image, int width, int height){
    uint8_t* rgb_image;
    rgb_image=malloc(width*height*3);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            rgb_image[(i*width+j)*3+0]=gray_image[i*width+j];
            rgb_image[(i*width+j)*3+1]=gray_image[i*width+j];
            rgb_image[(i*width+j)*3+2]=gray_image[i*width+j];
        }
    }
    return rgb_image;
}

void Set_Pixel_RGB(uint8_t* image,int width,int height,int x,int y,uint8_t R,uint8_t G,uint8_t B){
    image[(y*width+x)*3+0]=R;
    image[(y*width+x)*3+1]=G;
    image[(y*width+x)*3+2]=B;
}

void Set_Pixel_Gray(uint8_t* image,int width,int height,int x,int y,uint8_t intensity){
    image[y*width+x]=intensity;
}

int* Get_Histogram_Gray(uint8_t* buffer, int width, int height) {
	int* Histogram = malloc(256*sizeof(int));
	for (int i = 0; i < 256; i++) {
		Histogram[i] = 0;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Histogram[buffer[i*width + j]]++;
		}
	}
	return Histogram;
}

uint8_t* Get_Histogram_Image_Gray(int* histogram,int width,int height,int* histogram_width,int* histogram_height){
    int max=Max_Index(histogram,width*height);
    *histogram_height=histogram[max];
    *histogram_width=256;

    uint8_t* histogram_image=malloc(*histogram_width**histogram_height*3);
    for(int i=0;i<*histogram_height;i++){
        for(int j=0;j<*histogram_width;j++){
            histogram_image[(i**histogram_width+j)*3+0]=255;
            histogram_image[(i**histogram_width+j)*3+1]=255;
            histogram_image[(i**histogram_width+j)*3+2]=255;
        }
    }

    for(int i=0;i<256;i++){
        for(int j=0;j<=histogram[i];j++){
            histogram_image[((*histogram_height-j-1)*width+j)*3+0]=0;
            histogram_image[((*histogram_height-j-1)*width+j)*3+1]=0;
            histogram_image[((*histogram_height-j-1)*width+j)*3+2]=0;
        }
    }
    return histogram_image;
}