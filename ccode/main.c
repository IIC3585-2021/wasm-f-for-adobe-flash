#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char* fib(char* arr){

   printf("Data from the file:\n%s\n", arr);
   int cont = 0;
   int letter_number;
   int number = 0;
   while (arr[cont] != '\0'){
      if (arr[cont] > 64)
      {
         letter_number = arr[cont] - 65;
      } else if(arr[cont] > 47 )
      {
         letter_number = arr[cont] - 48;
      } else if(arr[cont] == 32 )
      {
      }
      cont ++;
   }

   return arr;

}


int main() {
   FILE *fptr;
   fptr = fopen("input.txt", "r");
   int matrix[27][27];
   char *arr  ;

   fscanf(fptr, "%m[^\n]", &arr);

   fclose(fptr);

   return 0;
}