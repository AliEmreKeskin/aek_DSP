int FIR_filter(int s[],int s_size,int coefficients[], int coefficients_size,int y[]){
    memset(y,0,s_size*sizeof(int));
    for(int n=0;n<s_size;n++){
        for(int k=0;k<coefficients_size;k++){
            if(n-k<0)continue;
            y[n]+=coefficients[k]*s[n-k];
        }
    }
}