#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>



int ary[27][27],completed[27],n=0,cost=0,i,c=0;
char* out;

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
 
	//printf("%d--->",city+1);
   out[c] = city+65;
   c++;
	ncity=least(city);
 
	if(ncity==999)
	{
		ncity=0;
		//printf("%d",ncity+1);
      out[c] = ncity+65;
      c++;
		cost+=ary[city][ncity];
 
		return;
	}
 
	mincost(ncity);
}
 

  
// int least(int c)
// {
// 	int i,nc=999;
// 	int min=999,kmin;
 
// 	for(i=0;i < n;i++)
// 	{
// 		if((ary[c][i]!=0)&&(completed[i]==0))
// 			if(ary[c][i]+ary[i][c] < min)
// 			{
// 				min=ary[i][0]+ary[c][i];
// 				kmin=ary[c][i];
// 				nc=i;
// 			}
// 	}
 
// 	if(min!=999)
// 		cost+=kmin;
 
// 	return nc;
// }

// void takeInput()
// {
// 	int i,j;
 
// 	printf("Enter the number of villages: ");
// 	scanf("%d",&n);
 
// 	printf("\nEnter the Cost Matrix\n");
 
// 	for(i=0;i < n;i++)
// 	{
// 		printf("\nEnter Elements of Row: %d\n",i+1);
 
// 		for( j=0;j < n;j++)
// 			scanf("%d",&ary[i][j]);
 
// 		completed[i]=0;
// 	}
 
// 	printf("\n\nThe cost list is:");
 
// 	for( i=0;i < n;i++)
// 	{
// 		printf("\n");
 
// 		for(j=0;j < n;j++)
// 			printf("\t%d",ary[i][j]);
// 	}
// }
 
// void mincost(int city, char* out, int* cou)
// {
// 	int i,ncity;
 
// 	completed[city]=1;
 
// 	out[cou[0]] = city+65;
//    cou[0] ++;
// 	ncity=least(city);
 
// 	if(ncity==999)
// 	{
// 		ncity=0;
// 		out[cou[0]] = ncity+65;
//       cou[0] ++;
// 		cost+=ary[city][ncity];
 
// 		return;
// 	}
 
// 	mincost(ncity, out, cou);
// }

char *findbest(char *arr)
{

   //printf("Data from the file:\n%s\n", arr);
   //Matrix *matrix = matrix_init(10);
   //int matrix[27][27];


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
         //printf("Arc:%d %d Letter: %c %c  Value:%d\n", posx, posy, posx+65,posy+65, value_number);
         //change_value_matrix(matrix, posx, posy, value_number);
         if (posx >= posy && posx>n)
         {
            n = posx;
            //printf("posx : %d, posy: %d, n: %d\n",posx,posy,n);
         }
         if (posy > posx && posy>n)
         {
            //printf("posx : %d, posy: %d, n: %d\n",posx,posy,n);
            n = posy;
         }
         ary[posx][posy] = value_number;
         ary[posy][posx] = value_number;
         decimal_pow = 1;
      }
      cont++;
   }

   //       for(int i = 0;i < 10;i++)
   // {
   //     for(int j = 0;j < 10;j++)
   // {
   //    ary[i][j]= matrix->arraylist_pointer[i]->array[j];
   // }
   // completed[i] = 0;
   // }

   // n= matrix->count+1;
   //char *output = malloc(sizeof(char) * (n+2));
   //int *arrcount = malloc(sizeof(int));
   //arrcount[0] = 0;
   //mincost(0, output, arrcount);
   //arrcount[0]++;
   //output[arrcount[0]] = '\0';
   //printf("%s\n", output);
   // while(*output!='\0')
   //      printf("%c",*output++);

   n ++;
      for(i = 0;i < n;i++)
      {
         completed[i] = 0;
      }
   //printf("then is %d\n",n);
   out = malloc(sizeof(char)*(n+2));
   for (i = 0;i < n;i++){
      for(int j = 0;j < n;j++)
      {
         if (i!=j && ary[i][j]==0)
         {
            ary[i][j] = 50;
         } 
      }
   }
   // printf("\n\nThe cost list is:");
 
	// for( i=0;i < n;i++)
	// {
	// 	printf("\n");
 
	// 	for(int j=0;j < n;j++)
	// 		printf("\t%d",ary[i][j]);
	// }
   mincost(0);

   out[n+1] = '\0';
   //printf("%d\n",n);
   //printf("%s\n", out);

   free(arr);

   return out;
}

uint64_t factorial(uint64_t n, uint64_t arr[])
{
   if (n >= 1)
   {
      uint64_t value = n * factorial(n - 1, arr);
      arr[n - 1] = value;
      return value;
   }
   else
   {
      return 1;
   }
}


int main()
{
   FILE *fptr;
   fptr = fopen("input.txt", "r");
   char *arr = NULL;
   //Matrix *graph_matrix = matrix_init(10);




   // uint64_t memory_to_ask[graph_matrix->count];
   // uint64_t factorial_array[graph_matrix->count];
   // uint64_t fact = factorial(graph_matrix->count, factorial_array);
   // combinatory(graph_matrix, memory_to_ask, factorial_array);


   // int max_hash = 102400;

   // int *hash_table_value = malloc(sizeof(int) * max_hash);
   // int *hash_table_of_hash_father = malloc(sizeof(int) * max_hash);

   // for (int i = 0; i < max_hash; i++)
   // {
   //    hash_table_value[i] = -2;
   //    hash_table_of_hash_father[i] = -2;
   // }

   // int initial_set[graph_matrix->count-1];

   // for (int i = 1; i <graph_matrix->count;i++){
   //    int arr[1]={i};
   //    hash_table_value[hash(i,arr,1)]=graph_matrix->arraylist_pointer[1]->array[i];
   //    initial_set[i] = i;
   // }

   //int co = cost_f(0,initial_set,graph_matrix->count-1, hash_table_value, hash_table_of_hash_father, memory_to_ask, graph_matrix);
   //printf("%d\n",co);

   fscanf(fptr, "%m[^\n]", &arr);
   findbest(arr);
   fclose(fptr);
   //(fib(arr, graph_matrix));
   // print_matrix(graph_matrix);
   // printf("%d\n", hash_table_of_hash_father[0]);



   //matrix_destroy(graph_matrix);
   // free(hash_table_value);
   // free(hash_table_of_hash_father);

   return 0;
}