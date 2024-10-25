#include<stdio.h>
#include"nhap.h"
#include"xuly.h"

#define MAX 50

int main(){
	int K;
   	char s1[MAX], s2[MAX], s3[MAX];
   
   	nhap(K,s1,s2,s3);
   	mahoa(K,s1,s2);
   	giaima(K,s2,s3);
}