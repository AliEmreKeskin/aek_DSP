#include "statistics.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    aek_image img=aek_imread("data/elma.jpg");
    img=aek_RGB_to_Gray(img);
    aek_setpixel3b(img,10,10,0,0,0);
    aek_color color;
    color.r=150;
    color.g=0;
    color.b=0;
    aek_setpixel(img,15,15,color);
    aek_imwrite_png(img,"out.png");

    //histogram
    int* histogram_gray=aek_histogram(img);
    for(int i=0;i<256;i++){
        printf("%d:\t%d\n",i,histogram_gray[i]);
    }

    //mean from histogram
    printf("******************\n");
    printf("normal sum:\t%f\n",     Sum_uint8(img.data,img.w*img.h));
    printf("normal mean:\t%f\n",    Mean_uint8(img.data,img.w*img.h));
    printf("normal variance:\t%f\n",Variance_uint8(img.data,img.w*img.h));
    printf("******************\n");
    printf("histogram sum:\t%f\n",  Sum_histogram(histogram_gray,256));
    printf("histogram mean:\t%f\n",  Mean_histogram(histogram_gray,256));
    printf("histogram variance:\t%f\n",  Variance_histogram(histogram_gray,256));

    /**********************/
    /*stream variance demo*/
    /**********************/

    int count=100;
    double* a=(double*) malloc(sizeof(double*)*count);
    for(int i = 0; i < count; i++)
    {
        a[i]=i;
    }
    double sum=Sum(a,count);
    double mean=Mean(a,count);
    double variance=Variance(a,count);

    printf("*********************\n");
    printf("Stream variance demo\n");
    printf("normal sum:\t%f\n",sum);
    printf("normal mean:\t%f\n",mean);
    printf("normal variance:\t%f\n\n",variance);

    struct stat stat0;
    stat0.length=0;
    stat0.mean=0.0;
    stat0.s=0.0;
    stat0.variance=0.0;

    struct stat* stat_ptr;
    stat_ptr=&stat0;

    for(int i=0;i<count;i++){
        VarianceStream(stat_ptr,i);
        printf("%d\t%f\t%f\n", stat_ptr->length, stat_ptr->mean, stat_ptr->variance);
    }
    return 0;
}


//#define CHANNEL_NUM 3

// int main() {

//     //read from file
//     int width, height, bpp;
//     uint8_t* rgb_image = stbi_load("data/elma.jpg", &width, &height, &bpp, 3);

//     //convert to grayscale
//     uint8_t* gray=RGB_to_Gray(rgb_image,width,height);

//     //resize
//     int small_width=100;
//     int small_height=50;
//     uint8_t* small_image=malloc(small_width*small_height*CHANNEL_NUM);
//     stbir_resize_uint8(rgb_image,width,height,0,small_image,small_width,small_height,0,CHANNEL_NUM);

//     //pixel manipulation
//     Set_Pixel_RGB(small_image,small_width,small_height,10,10,0,0,0);
//     Set_Pixel_Gray(gray,width,height,10,10,0);    

//     //write to file
//     uint8_t* gray_rgb=Gray_to_RGB(gray,width,height);
//     stbi_write_png("gray.png", width, height, CHANNEL_NUM, gray_rgb, width*CHANNEL_NUM);
//     stbi_write_png("small.png",small_width,small_height,CHANNEL_NUM,small_image,small_width*CHANNEL_NUM);

//     //free up memory
//     stbi_image_free(rgb_image);
//     stbi_image_free(gray);
//     stbi_image_free(gray_rgb);
//     stbi_image_free(small_image);

//     // //histogram
//     // int* histogram_gray=Get_Histogram_Gray(gray,width,height);
//     // for(int i=0;i<256;i++){
//     //     printf("%d:\t%d\n",i,histogram_gray[i]);
//     // }

//     // //mean from histogram
//     // printf("******************\n");
//     // printf("normal sum:\t%f\n",     Sum_uint8(gray,width*height));
//     // printf("normal mean:\t%f\n",    Mean_uint8(gray,width*height));
//     // printf("normal variance:\t%f\n",Variance_uint8(gray,width*height));
//     // printf("******************\n");
//     // printf("histogram sum:\t%f\n",  Sum_histogram(histogram_gray,256));
//     // printf("histogram mean:\t%f\n",  Mean_histogram(histogram_gray,256));
//     // printf("histogram variance:\t%f\n",  Variance_histogram(histogram_gray,256));

//     // // //not working
//     // // int histogram_width,histogram_height;
//     // // uint8_t* histogram_gray_image=Get_Histogram_Image_Gray(histogram_gray,width,height,&histogram_width,&histogram_height);
//     // // stbi_write_png("histogram.png",256,histogram_height,CHANNEL_NUM,histogram_gray_image,256*CHANNEL_NUM);
//     // // uint8_t* small_histogram_gray_image;
//     // // stbir_resize_uint8(histogram_gray_image,histogram_width,histogram_height,0,small_histogram_gray_image,256,256,0,CHANNEL_NUM);
//     // // stbi_write_png("small_histogram.png",256,256,CHANNEL_NUM,small_histogram_gray_image,256*CHANNEL_NUM);

    


//     return 0;
// }