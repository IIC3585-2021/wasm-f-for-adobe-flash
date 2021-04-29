#include <stdio.h>
#include <stdlib.h>
int main() {
   char *arr  ;
   FILE *fptr;
   fptr = fopen("input.txt", "r");

   fscanf(fptr, "%m[^\n]", &arr);
   printf("Data from the file:\n%s\n", arr);
   int cont = 0;
   int** matrix;
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
          printf("Single %c %d %d\n", arr[cont],arr[cont], letter_number);
      }
      cont ++;
   }

   fclose(fptr);
}