#ifndef IMAGE_H
#define IMAGE_H

uint8_t* RGB_to_Gray(uint8_t* rgb_image, int width, int height);
uint8_t* Gray_to_RGB(uint8_t* gray_image, int width, int height);
void Set_Pixel_RGB(uint8_t* image,int width,int height,int x,int y,uint8_t R,uint8_t G,uint8_t B);
void Set_Pixel_Gray(uint8_t* image,int width,int height,int x,int y,uint8_t intensity);
int* Get_Histogram_Gray(uint8_t* buffer, int width, int height);
uint8_t* Get_Histogram_Image_Gray(int* histogram,int width,int height,int* histogram_width,int* histogram_height);

typedef struct{
    int w,h,c;
    unsigned char *data;
} aek_image;

typedef struct{
    unsigned char r,g,b;
}aek_color;

aek_image aek_imread(char *filename);
void aek_imwrite_png(aek_image img, const char *name);
aek_image aek_RGB_to_Gray(aek_image img);
aek_image aek_Gray_to_RGB(aek_image img);
void aek_setpixel3b(aek_image img,int x,int y,unsigned char r,unsigned char g,unsigned char b);
void aek_setpixel(aek_image img,int x,int y,aek_color color);
int* aek_histogram(aek_image img);

#endif //IMAGE_H