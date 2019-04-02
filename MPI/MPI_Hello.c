# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>

/// Simplest program
/// Compile with 'mpicc MPI_Hello.c -o hello.out'
/// Run with 'mpirun -n <process_number> hello.out'

int main(int argc, char ** argv)
{
    int psize;
    int prank;
    MPI_Status status;

    int ierr;

    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &prank);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &psize);

    // root process
    if (prank == 0)
    {
        printf("The number of processes available is %d\n", psize);
    }

    printf("Hello world from process[%d]\n", prank);

    ierr = MPI_Finalize();

    return 0;
}
