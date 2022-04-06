#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
 
static void swap(unsigned int *a, unsigned int *b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}
 
static void traveling_salesman_recursive(unsigned int adjmat[26][26], unsigned int order, 
        unsigned int *best_tour, unsigned int *best_tour_cost, unsigned int *partial_tour,
        unsigned int *partial_tour_cost, unsigned int level)
{
    if (level == order - 1) {
        /* Add last two edges to complete the tour */
        unsigned int tour_cost = *partial_tour_cost 
                + adjmat[partial_tour[order - 2]][partial_tour[order - 1]]
                + adjmat[partial_tour[order - 1]][0];
        if (*best_tour_cost == 0 || tour_cost < *best_tour_cost) {
            /* Best tour so far */
            memcpy(best_tour, partial_tour, order * sizeof(unsigned int));
            *best_tour_cost = tour_cost;
        }
    }
    else {
        unsigned int i;
        for (i = level; i < order; i++) {
            if (*best_tour_cost == 0
                || *partial_tour_cost + adjmat[partial_tour[level - 1]][partial_tour[i]]
                    < *best_tour_cost)
            {  
                /* Next permutation */
                swap(&partial_tour[level], &partial_tour[i]);
                unsigned int cost = adjmat[partial_tour[level - 1]][partial_tour[level]];
                *partial_tour_cost += cost;
                traveling_salesman_recursive(adjmat, order, best_tour, best_tour_cost,
                        partial_tour, partial_tour_cost, level + 1);
                *partial_tour_cost -= cost;
                swap(&partial_tour[level], &partial_tour[i]);
            }
        }
    }
}
 
unsigned int traveling_salesman(unsigned int adjmat[26][26], unsigned int order, 
        unsigned int **best_tour)
{
    unsigned int i;
    unsigned int best_tour_cost = 0;
    unsigned int partial_tour_cost = 0;
    unsigned int *partial_tour = malloc(order * sizeof(unsigned int));
    *best_tour = malloc(order * sizeof(unsigned int));
    if (partial_tour == NULL || *best_tour == NULL) {
        free(partial_tour);
        free(*best_tour);
        *best_tour = NULL;
        return 0;
    }        
    for (i = 0; i < order; i++) {
        partial_tour[i] = i;
    }
    traveling_salesman_recursive(adjmat, order, *best_tour, &best_tour_cost, partial_tour, 
            &partial_tour_cost, 1);
    free(partial_tour);
    return best_tour_cost;
}

unsigned int change_str_to_int(char *arr, unsigned int mat[26][26]){
   int cont = 0;
   int letter_number;
   int posx;
   int posy;
   int cont_letter = 0;
   int decimal_pow = 1;
   int value_number = 0;
   unsigned int verts = 0;
   while (arr[cont] != '\0')
   {
      //printf("char: %c\n", arr[cont]);
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
         if (posx >= posy && posx>verts)
         {
            verts = posx;
            //printf("posx : %d, posy: %d, n: %d\n",posx,posy,n);
         }
         if (posy > posx && posy>verts)
         {
            //printf("posx : %d, posy: %d, n: %d\n",posx,posy,n);
            verts = posy;
         }
         //printf("posx : %d, posy: %d, value_number: %d\n",posx,posy,value_number);
         mat[posx][posy] = value_number;
         mat[posy][posx] = value_number;
         decimal_pow = 1;
      }
      cont++;
   }
   //printf("posx : %d, posy: %d, value_number: %d\n",posx,posy,value_number);
mat[posx][posy] = value_number;
         mat[posy][posx] = value_number;
   verts++;
   return verts;
}

void print_graph(unsigned int verts, unsigned int mat[26][26])
{
    int i, j;
    for (i = 0; i < verts; ++i, printf("\n"))
    for (j = 0; j < verts; ++j)
        printf("%d ", mat[i][j]);
}

void replace_zeros(int verts, unsigned int mat[26][26])
{
    int i, j;
    for (i = 0; i < verts; ++i){
        for (j = 0; j < verts; ++j){
            if(i != j && mat[i][j] == 0){
                mat[i][j] = 1000;
            }
        }
    }
}

char *findbest(char *arr)
{
    char* out;
    unsigned int adjmat[26][26] = {0};
    unsigned int order = change_str_to_int(arr, adjmat); /* Vertices */
    //printf("%u vertices\n", order);
    replace_zeros(order, adjmat);
    // print_graph(order, adjmat);
    unsigned int *best_tour;
    out = malloc(sizeof(char)*(order+2));
    out[order+1] = '\0';

    unsigned int cost = traveling_salesman(adjmat, order, &best_tour);
    unsigned int i;
    // printf("Best tour cost: %u\n", cost);
    // printf("Vertices:\n");
    for (i = 0; i < order; i++) {
        out[i] = best_tour[i]+65;
        // printf("%u ", best_tour[i]);
    }
    // putchar('\n');
    // printf("Edge weights:\n");
    for (i = 0; i < order - 1; i++) {
        // printf("%u ", adjmat[best_tour[i]][best_tour[i + 1]]);
    }
    // printf("%u\n", adjmat[best_tour[order - 1]][0]);
    free(best_tour);
    
    free(arr);

    //printf("%d\n",verts);
    // printf("%s\n", out);

    return out;

}

int main(void)
{
    
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    char *arr = NULL;
    fscanf(fptr, "%m[^\n]", &arr);
    findbest(arr);
    fclose(fptr);
    
    return 0;
}