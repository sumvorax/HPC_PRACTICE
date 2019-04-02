#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    MPI_Init(&argc, &argv);

    const int N = 10;
    float data[N];

    int psize;
    int prank;
    int source;
    int dest;
    int tag;

    MPI_Status status;
    int count;

    MPI_Comm_rank(MPI_COMM_WORLD, &prank);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);

    if (prank == 0)
    {
        dest = 1;
        tag = 0;

        printf("The number of processes available is %d\n", psize);

        for (int i = 0; i < N; ++i)
        {
            data[i] = i;
        }

        printf("p[%d]: has %d elements to send\n", prank, N);
        printf("p[%d]: which are:\n", prank);

        for (int i = 0; i < N; ++i)
        {
            printf("%f ", data[i]);
        }

        printf("\n");
        fflush(stdout);

        if (psize > 1)
        {
            MPI_Send(data, N, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
        }
        else
        {
            printf("p[%d]: nowhere to send\n", prank);
        }
    }
    else if (prank == 1)
    {
        source = 0;
        tag = 0;

        MPI_Recv(
            data, N, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status
        );
        MPI_Get_count(&status, MPI_FLOAT, &count);

        printf("p[%d]: received %d elements\n", prank, count);
        printf("p[%d]: which are:\n", prank);

        for (int i = 0; i < N; ++i)
        {
            printf("%f ", data[i]);
        }

        printf("\n");
        fflush(stdout);
    }
    else
    {
        printf("p[%d]: nothing to do\n", prank);
    }

    MPI_Finalize();

    return 0;
}
