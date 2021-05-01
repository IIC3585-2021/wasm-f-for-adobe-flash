#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/** Estructura de una arraylist */
struct arraylist_list
{
  int size;
  int count;
  int* array;
};


// Aquí le estoy poniendo un nombre más simple a la lista para no tener que
// referirme a la lista como struct arraylist_list
/** Estructura de una arraylist */
typedef struct arraylist_list ArrayList;

/** Estructura de una arraylist */
struct matrix_list
{
  int size;
  int count;
  ArrayList** arraylist_pointer;
};

typedef struct matrix_list Matrix;


ArrayList* arraylist_init(int length, int pos)
{
  ArrayList *new_array;
  new_array = malloc(sizeof(ArrayList));
  new_array -> size = length;
  new_array -> count = 0;
  new_array -> array = malloc(sizeof(int)*length);

  for(int i = 0;i < length;i++)
  {
     if (pos == i)
     {
        new_array -> array[i] = 0;
     } else{
        new_array -> array[i] = -1;
     }
  }

  return new_array;
}

Matrix* matrix_init (int length)
{
  Matrix *new_array;
  new_array = malloc(sizeof(Matrix));
  new_array -> size = length;
  new_array -> count = 0;
  new_array -> arraylist_pointer = malloc(sizeof(ArrayList*)*length);

  for(int i = 0;i < length;i++)
  {
     new_array -> arraylist_pointer[i] = arraylist_init(length, i);
  }

  return new_array;
}

/** Libera todos los recursos asociados a la lista */
void arraylist_destroy(ArrayList* list)
{
   free(list -> array);
   free(list);
}

   /** Libera todos los recursos asociados a la matrix */
void matrix_destroy(Matrix* matrix)
{

   for(int i = 0; i < matrix->size; i++)
   {
      arraylist_destroy(matrix->arraylist_pointer[i]);
   }
   free(matrix->arraylist_pointer);
   free(matrix);
}

/** Duplica size de un arraylist */
void expand_arraylist(ArrayList* list)
{

  int *big_array;
   int size;
   size = (list -> size);
   list -> size = size * 2;
   big_array = malloc(sizeof(int)*(size * 2));
   int i;
   for (i = 0; i < (list -> size)*2; i++ ) {
      if (i < size)
      {
         big_array[i] = list -> array[i];
      } else
      {
         big_array[i] = -1;
      }
   }
   free(list -> array);
   list -> array = big_array;
}

void expand_matrix(Matrix* matrix)
{
   ArrayList** big_array_pointer;
   int size;
   size = (matrix -> size);
   matrix -> size = size * 2;
   big_array_pointer = malloc(sizeof(ArrayList*)*matrix -> size);
   for (int i = 0; i < (matrix -> size);i++) {
      if (i < size)
   {
      expand_arraylist(matrix->arraylist_pointer[i]);
      big_array_pointer[i] = matrix->arraylist_pointer[i];
   } else
   {
      big_array_pointer[i] = arraylist_init(matrix -> size, i);
   }
   }
   free(matrix->arraylist_pointer);
   matrix->arraylist_pointer = big_array_pointer;

}

void change_value_matrix(Matrix* matrix, int posx, int posy, int value){
   while (posx > matrix->size -1  || posy > matrix->size -1)
   {
      expand_matrix(matrix);
   }
   matrix->arraylist_pointer[posx]->array[posy] = value;
   matrix->arraylist_pointer[posx]->count++;
   matrix->arraylist_pointer[posy]->array[posx] = value;
   matrix->arraylist_pointer[posy]->count++;
   matrix->count++;
}

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