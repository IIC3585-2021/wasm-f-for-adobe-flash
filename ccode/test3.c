#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


/** Estructura de una arraylist */
struct arraylist_list
{
   int size;
   int count;
   int *array;
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
   ArrayList **arraylist_pointer;
};

typedef struct matrix_list Matrix;

ArrayList *arraylist_init(int length, int pos)
{
   ArrayList *new_array;
   new_array = malloc(sizeof(ArrayList));
   new_array->size = length;
   new_array->count = 0;
   new_array->array = malloc(sizeof(int) * length);

   for (int i = 0; i < length; i++)
   {
      if (pos == i)
      {
         new_array->array[i] = 0;
      }
      else
      {
         new_array->array[i] = -1;
      }
   }

   return new_array;
}

Matrix *matrix_init(int length)
{
   Matrix *new_array;
   new_array = malloc(sizeof(Matrix));
   new_array->size = length;
   new_array->count = 0;
   new_array->arraylist_pointer = malloc(sizeof(ArrayList *) * length);

   for (int i = 0; i < length; i++)
   {
      new_array->arraylist_pointer[i] = arraylist_init(length, i);
   }

   return new_array;
}

/** Libera todos los recursos asociados a la lista */
void arraylist_destroy(ArrayList *list)
{
   free(list->array);
   free(list);
}

/** Libera todos los recursos asociados a la matrix */
void matrix_destroy(Matrix *matrix)
{

   for (int i = 0; i < matrix->size; i++)
   {
      arraylist_destroy(matrix->arraylist_pointer[i]);
   }
   free(matrix->arraylist_pointer);
   free(matrix);
}

void print_array(ArrayList *list, int limit)
{
   printf("[");
   for (int i = 0; i < limit - 1; i++)
   {
      printf("%d, ", list->array[i]);
   }
   printf("%d]\n", list->array[limit - 1]);
}

void print_matrix(Matrix *matrix)
{
   for (int i = 0; i < matrix->count + 1; i++)
   {
      print_array(matrix->arraylist_pointer[i], matrix->count);
   }
}

/** Duplica size de un arraylist */
void expand_arraylist(ArrayList *list)
{

   int *big_array;
   int size;
   size = (list->size);
   list->size = size * 2;
   big_array = malloc(sizeof(int) * (size * 2));
   int i;
   for (i = 0; i < (list->size) * 2; i++)
   {
      if (i < size)
      {
         big_array[i] = list->array[i];
      }
      else
      {
         big_array[i] = -1;
      }
   }
   free(list->array);
   list->array = big_array;
}

void expand_matrix(Matrix *matrix)
{
   ArrayList **big_array_pointer;
   int size;
   size = (matrix->size);
   matrix->size = size * 2;
   big_array_pointer = malloc(sizeof(ArrayList *) * matrix->size);
   for (int i = 0; i < (matrix->size); i++)
   {
      if (i < size)
      {
         expand_arraylist(matrix->arraylist_pointer[i]);
         big_array_pointer[i] = matrix->arraylist_pointer[i];
      }
      else
      {
         big_array_pointer[i] = arraylist_init(matrix->size, i);
      }
   }
   free(matrix->arraylist_pointer);
   matrix->arraylist_pointer = big_array_pointer;
}

void combinatory(Matrix *graph_matrix, uint64_t combinatory_array[], uint64_t factorial_array[])
{
   int limit = graph_matrix->count;
   //printf("limit is %d\n", limit);
   //printf("number is %" PRIu64 "\n", factorial(limit, factorial_array));
   uint64_t total_elemnts = 0;
   for (int i = 0; i < limit; i++)
   {
      uint64_t n = factorial_array[limit - 1];
      uint64_t n_minus_m = factorial_array[limit - 2 - i];
      if (n_minus_m == 0)
      {
         n_minus_m = 1;
      }
      uint64_t m = factorial_array[i];
      uint64_t value = 1;
      if (limit - 1 - i > 0)
      {
         value = n / (n_minus_m * m);
      }
      combinatory_array[i] = value;
      // total_elemnts += value;
      printf("%d!/(%d!*%d!)\n", limit, limit - i - 1, i + 1);
      printf("%" PRIu64 "/(%" PRIu64 "*%" PRIu64 ") = %" PRIu64 " \n", n, n_minus_m, m, value);
   }
   //printf("number is %" PRIu64 "\n", total_elemnts);
}

void change_value_matrix(Matrix *matrix, int posx, int posy, int value)
{
   int maximun;
   if (posx > posy)
   {
      maximun = posx;
   }
   else
   {
      maximun = posy;
   }
   while (posx > matrix->size - 1 || posy > matrix->size - 1)
   {
      printf("entre\n");
      expand_matrix(matrix);
   }
   matrix->arraylist_pointer[posx]->array[posy] = value;
   matrix->arraylist_pointer[posx]->count++;
   matrix->arraylist_pointer[posy]->array[posx] = value;
   matrix->arraylist_pointer[posy]->count++;
   if (maximun > matrix->count)
   {
      matrix->count = maximun;
   }
}


int hash(int number, int arr[], int length)
{
   int hash_number = 0;
   for (int i = 0; i < length; i++)
   {
      hash_number += arr[i];
   }
   return hash_number * length * number;
}

int min(int arr_values[], int length_arr_values)
{
   int minimum;
   int found_first = 0;
   for (int i = 0; i < length_arr_values; i++)
   {
      if (found_first == 0 && arr_values[i] != -1)
      {
         minimum = arr_values[i];
         found_first = 1;
      }
      else if (found_first != 0 && arr_values[i] != -1 && arr_values[i] < minimum)
      {
         minimum = arr_values[i];
      }
   }
   if (found_first == 0)
   {
      minimum = -1;
   }
   return minimum;
}

void combinationUtil(int arr[], int data[], int start, int end,
                     int index, int r, int **ar, int *c)
{
   // Current combination is ready to be printed, print it
   uint64_t h;
   if (index == r)
   {
      int s;
      s = c[0];
      ar[s] = malloc(sizeof(int) * r);
      for (int j = 0; j < r; j++)
      {
         //h = hash(data[j],data,r);
         ar[s][j] = data[j];
      }
      c[0]++;
      return;
   }
   // replace index with all possible elements. The condition
   // "end-i+1 >= r-index" makes sure that including one element
   // at index will make a combination with remaining elements
   // at remaining positions
   for (int i = start; i <= end && end - i + 1 >= r - index; i++)
   {
      data[index] = arr[i];
      combinationUtil(arr, data, i + 1, end, index + 1, r, ar, c);
   }
}

int cost_f(int numb, int set_numb[], int lenght_set, int *hash_table_values, int *hash_table_of_hash_father, uint64_t memory_to_ask[], Matrix *matrix)
{
   int h = hash(numb, set_numb, lenght_set);
   if (hash_table_values[h] != -2)
   {
      return hash_table_values[h];
   }
   else
   {
      int **arr = malloc(sizeof(int *) * memory_to_ask[lenght_set - 1]);
      int *c = malloc(sizeof(int));
      c[0] = 0;
      int data[lenght_set];
      int result;
      combinationUtil(set_numb, data, 0, matrix->count - 1, 0, lenght_set, arr, c);
      for (int i = 0; i < memory_to_ask[lenght_set - 1]; i++)
      {
         int *min_array = malloc(sizeof(int) * lenght_set - 1);
         for (int j = 0; j < lenght_set; j++)
         {
            int *sub_set = malloc(sizeof(int) * lenght_set - 1);
            for (int k = 0; k < lenght_set; k++)
            {
               if (j != k)
               {
                  sub_set[k] = arr[i][j];
               }
            }
            for (int p = 0; p < lenght_set - 1; p++)
            {
               min_array[p] = cost_f(sub_set[p], sub_set, lenght_set - 1, hash_table_values, hash_table_of_hash_father, memory_to_ask, matrix) + matrix->arraylist_pointer[sub_set[p]]->array[j];
            }
            int result = min(min_array, lenght_set - 1);
            int h = hash(j, set_numb, lenght_set);

            hash_table_values[h] = result;
            hash_table_of_hash_father[h] = hash_table_values[h];
            free(sub_set);
         }
         free(min_array);
      }
      free(c);
      free(arr);
      return result;
   }
}
