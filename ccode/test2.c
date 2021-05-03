#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t hash(int number, int arr[], int length){
   uint64_t hash_number = 0;
   for (int i = 0; i < length; i++)
   {
      hash_number += arr[i];
   }
   return hash_number * length * number;
}

void combinationUtil(int arr[], int data[], int start, int end,
                     int index, int r, int** ar, int* c);
 
// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(int arr[], int n, int r, int** ar, int* c)
{
    // A temporary array to store all combination one by one
    int data[r];
 
    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, data, 0, n-1, 0, r, ar, c);
}
 
/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed */
void combinationUtil(int arr[], int data[], int start, int end,
                     int index, int r, int** ar, int* c)
{
    // Current combination is ready to be printed, print it
    uint64_t h;
    if (index == r)
    {
        int s;
        s = c[0];
        ar[s] = malloc(sizeof(int)*r);
        for (int j=0; j<r; j++){
            //h = hash(data[j],data,r);
            ar[s][j] = data[j];
    }
    c[0] ++;
    return;
    }
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r, ar, c);
    }
}
// Driver program to test above functions
int main()
{
    int arr[] = {2, 3, 4, 5};
    int** ar =malloc(sizeof(int*)*6);
    int r = 2;
    int* c = malloc(sizeof(int));
    c[0] = 0;
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("%d\n",n);
    printCombination(arr, n, r, ar,c);
    for(int i = 0;i < 6;i++)
    {
        for(int j = 0;j < r;j++)
    {
        printf("%d", ar[i][j]);
    }
    printf("\n");
    }
}