/*
Travelling Salesman Problem using dynamic programming
Held-Karp's algo 
References:
https://en.wikipedia.org/wiki/Held–Karp_algorithm
Bitmasking - https://www.geeksforgeeks.org/bitmasking-dynamic-programming-set-2-tsp/
https://cs.stackexchange.com/questions/16474/traveling-salesman-with-held-and-karp-algorithm
You may also want to read about memoization.
Note:
This program only has 0-based indexing.
Wikipedia uses the g(vertex, unvisited set) notation. 
Doing it that way is hard to implement.
My equivalent is h(vertex, visited set) = dp[vertex][visited set in bitmask]
where visited set = set of all vertices - unvisited set.
The equivalent of Wikipedia's g(2, {3, 4}) would be h(1, {0, 1}).
* h and tsp function are not exactly the same, parameters-wise.
Input Format:
No. of vertices, followed by all values of adj matrix 
Output Format:
Minimum tour distance, minimum tour, 
Intermediate calculations (optional) -- uncomment it out if you want to look at it
Time Complexity:
O(2^n * n^2) - same as brute force approach
Having said that, this algorithm is faster than brute force approach.
*/

#include <stdio.h>
#include <stdbool.h> // for bool data type
//#include <limits.h> // for INT_MAX
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int maxint = 100000/2; // A large value of my choosing.
//typedef int set; // set is now an alias of int

// In my system, INT_MAX = (7fffffff)h = (2147483647)decimal
// That's 31 ones in binmat. 
// But using such large values has been known to
// cause static memory allocation to fail.

// We'll use a maximum of 10. 
//#define 26 (26) 
//#define (1<<26 - 1) (1<<26 - 1)

// Global variables
int mat[26][26];
int verts; // no. of vertices
int limit; // A set containing all vertices.
int dp[26][32769]; // Dynamic programming table. 


int two_power(int exponent)
{
	return 1 << exponent; // pow(2, exponent)
}

void initialize_limit(int verts)
{
	limit = two_power(verts) - 1;
	printf("limit: %d\n", limit)
	// Suppose verts is 4,
	// 2^4 - 1 = 15 = (1111)bin
}

void initialize_dp(int verts, int limit)
{
	int i, j;
	for (i = 0; i < verts; ++i)
	for (j = 0; j <= limit; ++j) dp[i][j] = -1;
}

bool all_visited(int bitmask)
{
	return bitmask == limit;	
}

bool is_visited(int bitmask, int vertex)
{
	// pow(2, i) = a bit pattern where only ith bit is set
	return bitmask & two_power(vertex); // Checks whether `vertex`th bit is set or cleared in bitmask
}

void mark_visited(int* bitmask, int vertex)
{
	// 1 << i = pow(2, i) =* a bit pattern where only ith bit is set
	*bitmask = (*bitmask) | two_power(vertex); // Sets the `vertex`th bit in bitmask
}

void print_vx_and_set(int parent_vx, int cur_set)
{
	printf("(%d, ", parent_vx);
	printf("{");
	for (int i = 0; i < verts; ++i)
	{
		int res = (~cur_set) & two_power(i);
		if (res) printf("%d ", i);
	}
	printf("})");
}

void print_dp()
{
	int i, j;
	for (i = 0; i < verts; ++i)
	for (j = 0; j <= limit; ++j)
	{
		if (dp[i][j] != -1)
		{
			printf("g");
			print_vx_and_set(i, j);
			printf(" = ");
			printf("%d ", dp[i][j]);
			printf("\n");
		}
	}
}

// The most important function.
int tsp(int parent_vx, int cur_set)
{
	mark_visited(&cur_set, parent_vx);

	if (all_visited(cur_set)) 
	{
		dp[parent_vx][cur_set] = mat[parent_vx][0];	
		return mat[parent_vx][0]; 
	}

	// If value has already been calculated, then just return it
	if (dp[parent_vx][cur_set] != -1)
	{
		return dp[parent_vx][cur_set];
	}

	int distance, min_distance = maxint;

	// Calls tsp recursively on all non-visited vertices.
	// Since 0 is source, we don't start cur_vx at 0.
	for (int cur_vx = 1; cur_vx < verts; cur_vx++)
	{
		if (is_visited(cur_set, cur_vx) == false)
		{
			distance = mat[parent_vx][cur_vx] + tsp(cur_vx, cur_set); 
			if (min_distance > distance)
			{
				min_distance = distance;
			}
		}
	}

	dp[parent_vx][cur_set] = min_distance; // Storing result for later
	return min_distance;
}

// Prints out the tour looking at dp 
void traceback(int min_distance, char *out)
{
	int cur_set = 0;
	int cur_vx = 0;
	mark_visited(&cur_set, 0);
	int distance;

	// We start from g(1, {2, 3, 4, ... verts}) or h(0, {0})
	// and find out where the minimum came from. 

	// Say we have four vertices.
	// h(0, {0})              = min(mat[0][1] + h(1, {0, 1}),
	//		                    mat[0][2] + h(2, {0, 2}),
	//		                    mat[0][3] + h(3, {0, 3}))
	// Suppose the first one amounts to minimum ie min_distance.
	// Subtract mat[0][1] from min_distance
	// h(1, {0, 1}) =           min(mat[1][2] + h(1, {0, 1, 2}),
	//		                    mat[1][3] + h(3, {0, 1, 3}))
	// There are totally three of such iterations for four vertices.

	// printf("Tour: 0 -> ");
	int c = 0;
	out[c] = 65;
	c++;
	for (int i = 0; i < verts - 1; ++i)
	{
		for (int parent_vx = 1; parent_vx < verts; ++parent_vx)
		{
			if (is_visited(cur_set, parent_vx) == false)
			{
				int new_set = cur_set;
				mark_visited(&new_set, parent_vx);
			
				distance = mat[cur_vx][parent_vx] + dp[parent_vx][new_set];
				if (distance == min_distance)
				{
					printf("%d -> ", parent_vx);
					out[c] = parent_vx+65;
					c++;

					min_distance -= mat[cur_vx][parent_vx];

					// Update cur_vx and cur_set 
					cur_vx = parent_vx;
					cur_set = new_set;
					break;
				}
			}
		}
	}
	//printf("0");
}

// Graphs for TSP are usually complete graphs.
void read_graph(int verts, int mat[26][26])
{
	int i, j;
	for (i = 0; i < verts; ++i)
	{
		for (j = 0; j < verts; ++j)
		{
			scanf("%d", &mat[i][j]);
		}
	}
}
void print_graph(int verts, int mat[26][26])
{
	int i, j;
	for (i = 0; i < verts; ++i, printf("\n"))
	for (j = 0; j < verts; ++j)
		printf("%d ", mat[i][j]);
}

void change_str_to_int(char *arr){
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
   verts++;
}

char *findbest(char *arr)
{
	char* out;
	change_str_to_int(arr);
	initialize_limit(verts);
	initialize_dp(verts, limit);
	print_graph(verts, mat);

	int nullset = 0; 
	int min_dist = tsp(0, nullset);
   	out = malloc(sizeof(char)*(verts+2));

	traceback(min_dist, out);
	out[verts+1] = '\0';
	free(arr);

	//printf("%d\n",verts);
    printf("%s\n", out);

    return out;

}

int main()
{
	FILE *fptr;
   fptr = fopen("input.txt", "r");
   char *arr = NULL;
   fscanf(fptr, "%m[^\n]", &arr);
   findbest(arr);
   fclose(fptr);
	//print_dp();

	return 0;
}