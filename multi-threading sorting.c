#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define NUMBER_OF_THREADS 4



void *do_the_sorting(void *params);    /* thread that performs basic sorting algorithm */
void *do_the_merging(void *params);    /* thread that performs merging of results */


int my_array[SIZE] = {7,12, 19, 3, 18, 4, 2, 6, 15, 8};
int result[SIZE];
typedef struct
{
    int from_index;
    int to_index;
} the_range;


int main (int argc, const char * argv[])
{
    int i;
    pthread_t workers[NUMBER_OF_THREADS];

    /* create the first sorting thread */
    the_range *the_range_data = (the_range *) malloc (sizeof(the_range));
    the_range_data->from_index = 0;
    the_range_data->to_index = (SIZE/3) - 1;
    pthread_create(&workers[0], 0, do_the_sorting, the_range_data);
    /* create the second sorting thread */
    the_range_data = (the_range *) malloc (sizeof(the_range));
    the_range_data->from_index = (SIZE/3);
    the_range_data->to_index = SIZE - 1;
    pthread_create(&workers[1], 0, do_the_sorting, the_range_data);

    /** create the third sorting thread */
    the_range_data = (the_range *) malloc (sizeof(the_range));
    the_range_data->from_index = (SIZE/3);
    the_range_data->to_index = SIZE - 1;
    pthread_create(&workers[2], 0, do_the_sorting, the_range_data);



    /* we are waiting for the 3 sorting threads to finish 
        we are using pthread_join
    */
    for (i = 0; i < NUMBER_OF_THREADS - 1; i++){
        pthread_join(workers[i], NULL);
    }

    /* Let's build the merge thread (4th) */
    the_range_data = (the_range *) malloc(sizeof(the_range));
    the_range_data->from_index = 0;
    the_range_data->to_index = (SIZE/3);
    pthread_create(&workers[3], 0, do_the_merging, the_range_data);
    
    /* here we are waiting for the merge thread to finish, by calling the pthread_join function */
    pthread_join(workers[3], NULL);
   

    return 0;
}


/* function implementation */

void *do_the_sorting(void *params)
{
    the_range* my_pointer = (the_range *)params;
    //SORT
    int begin = my_pointer->from_index;
    int end = my_pointer->to_index+1;
    int z;
    for(z = begin; z < end; z++)
    {
        printf("The array we got is: %d\n", my_array[z]);
    }
    printf("\n");
    int i,j,t,k;
    for(i=begin; i< end; i++)
    {
        for(j=begin; j< end-i-1; j++)
        {
            if(my_array[j] > my_array[j+1])
            {
                t = my_array[j];
                my_array[j] = my_array[j+1];
                my_array[j+1] = t;
            }
        }
    }
    for(k = begin; k< end; k++){
            printf("Sorted array: %d\n", my_array[k]);
    }
    int x;
    for(x=begin; x<end; x++)
    {
            result[x] = my_array[x];
    }
    printf("\n");
    pthread_exit(0);
}
void *do_the_merging(void *params)
{
    the_range* my_pointer = (the_range *)params;
   //Let's Merge
   
    int begin = my_pointer->from_index;  
    int end = my_pointer->to_index+1;
    int i,j,t;
   
    for(i=begin; i< end; i++){
        for(j=begin; j< end-i; j++){
            if(result[j] > result[j+1]){
                t = result[j];
                result[j] = result[j+1];
                result[j+1] = t;
            }
        }
    }

    int d;
    for(d=0; d < SIZE; d++){
        printf("Final array (Result) is: %d\n", result[d]);
    }
    pthread_exit(0);
}
