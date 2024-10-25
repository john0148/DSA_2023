#include<stdio.h>
#include"nhap.h"

void nhap(int &K, char s1[], char s2[], char s3[]){
   printf("Nhap vao duong link file van ban = ");
   scanf(" %[^\n]",s1);
   printf("Nhap vao duong link file ma hoa = ");
   scanf(" %[^\n]",s2);
   printf("Nhap vao duong link file giai ma = ");
   scanf(" %[^\n]",s3);
   printf("Nhap vao so nguyen K = ");
   scanf("%d",&K);
}