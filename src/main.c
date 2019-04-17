#include "statistics.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include "conv.h"
#include "FIR_filter.h"

int main() {
    //image operations
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

    /*****************/
    /*  Convolution  */
    /*****************/
    printf("*********************\n");
    printf("Convolution Demo\n");
    int s_size=9;
    int h_size=4;
    double s[]={0,-1,-1.2,2,1.2,1.2,0.7,0,-0.7};
    double h[]={1,-0.5,-0.2,-0.1};
    double y[s_size+h_size-1];

    int temp=conv2(s,s_size,h,h_size,y);
    for(int i=0;i<s_size+h_size-1;i++){
        printf(" %.2f \n",y[i]);
    }

    /**************/
    /* FIR Filter */
    /**************/
    int signal_size = 6;
    int signal[]={1,2,3,4,5,6};
    int coefficients_size=5;
    int coefficients[]={-2,0,1,2,3};
    int output_y[signal_size];
    FIR_filter(signal,signal_size,coefficients,coefficients_size,output_y);
    printf("*********************\n");
    printf("FIR Filter Demo\n");
    for(int i=0;i<signal_size;i++){
        printf("%d\n",output_y[i]);
    }

    return 0;
}