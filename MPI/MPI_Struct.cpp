#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

struct Jumble
{
    char a;
    double b[2];
    unsigned int c[3];
};

int main(int argc, char ** argv)
{
    MPI_Init(&argc, &argv);

    const unsigned int size = 100;
    Jumble arr[size];

    int prank;
    MPI_Status status;

    MPI_Datatype Jumble_MPI_Type;
    MPI_Datatype types[3] = { MPI_CHAR, MPI_DOUBLE, MPI_UNSIGNED };
    int block_lens[3] = { 1, 2, 3 };
    MPI_Aint disps[3];

    MPI_Get_address(&arr[0].a, &disps[0]);
    MPI_Get_address(&arr[0].b, &disps[1]);
    MPI_Get_address(&arr[0].c, &disps[2]);

    disps[2] -= disps[0];
    disps[1] -= disps[0];
    disps[0] = 0;

    MPI_Type_create_struct(3, block_lens, disps, types, &Jumble_MPI_Type);
    MPI_Type_commit(&Jumble_MPI_Type);

    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    arr[0].c[1] = prank? 202: 101;
    printf("BEFORE [%d]: %d\n", prank, arr[0].c[1]);

    if (prank == 0)
    {
        MPI_Send(arr, size, Jumble_MPI_Type, 1, 42, MPI_COMM_WORLD);
    }
    else if (prank == 1)
    {
        MPI_Recv(arr, size, Jumble_MPI_Type, 0, 42, MPI_COMM_WORLD, &status);
    }

    printf("AFTER [%d]: %d\n", prank, arr[0].c[1]);

    //MPI_Type_free(&Jumble_MPI_Type);

    MPI_Finalize();

    return 0;
}
