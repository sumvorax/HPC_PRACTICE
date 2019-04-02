#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/// Simplest program
/// Compile with 'mpicc MPI_Hello.c -o hello.out -fopenmp'
/// Run with 'mpirun -n <process_number> ./hello.out'

int main(int argc, char ** argv)
{
    int required;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &required);

    int psize;
    int prank;

    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &prank);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);

    omp_set_num_threads(2);

    /// root process
    if (prank == 0 && omp_get_thread_num() == 0)
    {
        if (required == MPI_THREAD_MULTIPLE)
        {
            printf("Program has access to multiple threads per process\n");
        }
        else
        {
            printf("Program has no access to multiple threads per process\n");
        }

        printf("The number of processes available is %d\n", psize);
        printf(
            "The number of threads available per process is %d\n",
            omp_get_num_threads()
        );
    }

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello from thread[%d] from process[%d]\n", tid, prank);
    }

    MPI_Finalize();

    return 0;
}

