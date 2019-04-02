#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    MPI_Init(&argc, &argv);

    MPI_Status status;
    MPI_Request request;
    int ierr;

    int psize;
    int prank;
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);

    int source = (prank - 1 + psize) % psize;
    int dest = (prank + 1) % psize;

    const int N = 10;
    int count = 0;

    // try to uncomment
    // try to swap isend and irecv
    while (count < N)
    {
        ++count;

        MPI_Isend(
            &count, 1, MPI_INT, dest, prank, MPI_COMM_WORLD, &request
        );
        printf("p[%d] sent count %d to p[%d]\n", prank, count, dest);

        // MPI_Wait(&request, &status);

        // just CPU time consuming
        int a = N * N / (N + 1) * (N + 2) / (N + 3);
        int b = (N - 1) * (N + 1) / a;

        MPI_Irecv(
            &count, 1, MPI_INT, source, source, MPI_COMM_WORLD, &request
        );
        printf("p[%d] received count %d from p[%d]\n", prank, count, source);

        // MPI_Wait(&request, &status);
    }

    MPI_Finalize();

    return 0;
}
