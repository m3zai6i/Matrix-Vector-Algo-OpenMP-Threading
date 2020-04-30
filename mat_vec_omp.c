/* 
	Matrix-Vector Multiplication
	Parallel using Threading in Open-MP
*/

// Compile: gcc <filename>.c -fopenmp
// Run: ./a.out <rows> <columns>
// e.g. ./a.out 4 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[])
{

	clock_t start, end;
    double cpu_time_used;
    start = clock();

	//Taking arguments from the user
	int r = atoi(argv[1]); 
	int c = atoi(argv[2]);

	//int mat[r][c],vec[c],res[r];
	//=====================================================================
	//dynamic memory allocation 
    
    int **mat = (int **)malloc(r * sizeof(int *)); //matrix
    for (int i=0; i<r; i++) 
         mat[i] = (int *)malloc(c * sizeof(int)); 

    int *vec = (int *) malloc(c * sizeof(int)); //vector
	int *res = (int *) malloc(r * sizeof(int)); //Result vector
		
	int i,j;
	int count=0;

	//Matrix Initialization in sequence
	printf("Our Matrix is = \n");
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			mat[i][j] = ++count;
			printf("%4d\t", mat[i][j]);
		}
		printf("\n");
	}	
	
	count = 0;
	//Vector Initialization in sequence
	printf("Our Vector is = \n");
	for (i = 0; i < c; i++)
	{
		vec[i] = ++count;
		printf("%4d\n",vec[i]);
	}

	//########################################################################
 	//Matrix-Vector Sequential Algo
 	/* PARALLEL REGION STARTS */
	#pragma omp parallel shared(r,c,mat,vec,res) private(i,j)
	{
		#pragma omp for
		for ( i = 0; i < r; i++ ) 
		{
			res[i] = 0;
			for ( j = 0; j < c; j++ )
			{
				res[i] += mat[i][j]*vec[j];
			}

			//printf("Thread %d executes i=%d\n",omp_get_thread_num(),i);
		}
	} /* PARALLEL REGION ENDS */
	//########################################################################

	//Printing Result
	printf("Our Result Vector is = \n");
	for (i = 0; i < r; i++)
    {
	    printf("%4d\n",res[i]);
 	}

 	end = clock();
 	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

 	printf("\nTime to execute = %f seconds.\n", cpu_time_used);
 	//printf("Time = %ld \n", end-start);

 	return 0;
}

// For more optimized version --> E-mail: m3zai6i@gmail.com

