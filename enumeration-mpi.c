#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_TAG 0

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int procs_num;
    MPI_Comm_size(MPI_COMM_WORLD, &procs_num);
    MPI_Status status;

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int n, number;
    FILE *file = fopen("entrada16.in", "r");

    fscanf (file, "%d", &n);
    int *array  = calloc (n, sizeof(int));
    int *rank   = calloc (n, sizeof(int));
    for (int i = 0; i < n; ++i)
      fscanf (file, "%d", &array[i]);


    for (int i = my_rank * (n/procs_num); i < (my_rank+1) * (n/procs_num); ++i)
    {
        for (int j = i+1; j < n; ++j)
            if (array[i] >= array[j])
                rank[i]++;
            else
                rank[j]++;
    }

    printf("process %d/%d done\n", my_rank+1, procs_num);

    if (my_rank != 0)
        MPI_Send(rank, n, MPI_INT, 0, STD_TAG, MPI_COMM_WORLD);
    else
    {
        int *rank_received = calloc (n*procs_num, sizeof(int));

        for (int p = 1; p < procs_num; p++)
        {
            memset (rank_received, 0, n*sizeof(int));
            MPI_Recv(rank_received, n, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            for (int i = 0; i < n; ++i)
                rank[i] += rank_received[i];
        }

        int *result = calloc (n*procs_num, sizeof(int));

        for (int i = 0; i < n; ++i)
            result[rank[i]] = array[i];

        FILE *result_fp = fopen("saida.txt", "w+");
        for (int i = 0; i < n; ++i)
            fprintf(result_fp, "%d ", result[i]);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
