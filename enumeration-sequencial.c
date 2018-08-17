#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 15

int main(int argc, char **argv)
{
	int N = 60000;
	
	int *array  = calloc (N, sizeof(int));
	int *rank   = calloc (N, sizeof(int));
	int *result = calloc (N, sizeof(int));

	srand(SEED);

	for (int i = 0; i < N; ++i)
		array[i] = rand();

	printf("INPUT ARRAY:\n");
	for (int i = 0; i < N; ++i)
		printf("%d ", array[i]);
	printf("\n===================\n");
	

	for (int i = 0; i < N-1; ++i)
		for (int j = i+1; j < N; ++j)
			if (array[i] >= array[j])
				rank[i]++;
			else
				rank[j]++;

	for (int i = 0; i < N; ++i)
		result[rank[i]] = array[i];

	printf("OUTPUT ARRAY:\n");
	for (int i = 0; i < N; ++i)
		printf("%d ", result[i]);
	
	free(array);
	free(rank);
	free(result);

	return 0;
}