#include<stdio.h>
#include<ctype.h>
#include"xuly.h"

void mahoa(int K,char name_file_1[], char name_file_2[]){
   FILE *f = fopen(name_file_1,"r");
   FILE *g = fopen(name_file_2,"w");
   if(f == NULL || g == NULL){
      puts("File khong the mo duoc.");
   }
   else{
      char c;
      while((c = fgetc(f)) != EOF){
         if(isalpha(c)){
            char str = 'A'+(c-'A' + K%26 + 26)%26;
            fprintf(g,"%c",str);
         }
         else{
            fprintf(g,"%c",c);  
         }
      }
      fclose(g);
      fclose(f);
   }
}

void giaima(int K,char name_file_1[], char name_file_2[]){
   mahoa(-K,name_file_1,name_file_2);
}