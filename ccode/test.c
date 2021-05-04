#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>



int ary[10][10],completed[10],n,cost=0;

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

void print_array(ArrayList *list, int limit, int row)
{
   for (int i = 0; i < limit - 1; i++)
   {
      ary[row][i] = list->array[i];
   }
}

void print_matrix(Matrix *matrix)
{
   for (int i = 0; i < matrix->count + 1; i++)
   {
      print_array(matrix->arraylist_pointer[i], matrix->count, i);
      completed[i] = 0;
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
char *fib(char *arr, Matrix *matrix)
{

   printf("Data from the file:\n%s\n", arr);
   int cont = 0;
   int letter_number;
   int posx;
   int posy;
   int cont_letter = 0;
   int decimal_pow = 1;
   int value_number = 0;
   while (arr[cont] != '\0')
   {
      if (arr[cont] > 64)
      {
         letter_number = arr[cont] - 65;
         //printf("Number:%d Letter: %c\n", letter_number, arr[cont]);
         if (cont_letter % 2 == 0)
         {
            posx = letter_number;
         }
         else
         {
            posy = letter_number;
            // printf("Arc:%d %d Letter: %c %c\n", posx, posy, posx+65,posy+65);
         }
         cont_letter++;
      }
      else if (arr[cont] > 47)
      {
         letter_number = arr[cont] - 48;
         //printf("Number:%d Letter: %c\n", letter_number, arr[cont]);
         if (decimal_pow == 1)
         {
            value_number = letter_number;
            decimal_pow = decimal_pow * 10;
         }
         else
         {
            value_number = value_number * decimal_pow + letter_number;
         }
      }
      else if (arr[cont] == 32)
      {
      }
      else
      {
         // printf("Arc:%d %d Letter: %c %c  Value:%d\n", posx, posy, posx+65,posy+65, value_number);
         change_value_matrix(matrix, posx, posy, value_number);
         decimal_pow = 1;
      }
      cont++;
   }

   return arr;
}


void takeInput()
{
int i,j;

printf("Enter the number of villages: ");
scanf("%d",&n);

printf("\nEnter the Cost Matrix\n");

for(i=0;i < n;i++)
{
    printf("\nEnter Elements of Row: %d\n",i+1);

    for( j=0;j < n;j++)
        scanf("%d",&ary[i][j]);

    completed[i]=0;
}

printf("\n\nThe cost list is:");

for( i=0;i < n;i++)
{
    printf("\n");

    for(j=0;j < n;j++)
        printf("\t%d",ary[i][j]);
}
}

int least(int c)
{
	int i,nc=999;
	int min=999,kmin;
 
	for(i=0;i < n;i++)
	{
		if((ary[c][i]!=0)&&(completed[i]==0))
			if(ary[c][i]+ary[i][c] < min)
			{
				min=ary[i][0]+ary[c][i];
				kmin=ary[c][i];
				nc=i;
			}
	}
 
	if(min!=999)
		cost+=kmin;
 
	return nc;
}
 

void mincost(int city)
{
int i,ncity;

completed[city]=1;

printf("%d--->",city+1);
ncity=least(city);

if(ncity==999)
{
    ncity=0;
    printf("%d",ncity+1);
    cost+=ary[city][ncity];

    return;
}

mincost(ncity);
}

int main()
{
//takeInput();

FILE *fptr;
fptr = fopen("input.txt", "r");
char *arr = NULL;
Matrix *graph_matrix = matrix_init(10);

fib(arr, graph_matrix);
//print_matrix(graph_matrix);
n=graph_matrix->count;

printf("\n\nThe Path is:\n");
//mincost(0); //passing 0 because starting vertex

// printf("\n\nMinimum cost is %d\n ",cost);

return 0;
}