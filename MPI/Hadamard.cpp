#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

//============================================================================//
//  Hadamard (element-wise) product of two vectors
//============================================================================//
/// Compile with 'g++ MPI_Hello.cpp -o hello.out'
/// Run with './hello.out'

/// TASK: Parallelize using MPI + OpenMP

typedef std::default_random_engine randgen_t;
typedef std::uniform_int_distribution<int> udist_t;

void RandInit(randgen_t & generator, const int size, int * arr)
{
    udist_t distribution(0, 100);

    for (int i = 0; i < size; ++i)
    {
        arr[i] = distribution(generator);
    }

    return;
}

void Print(const int size, const int * arr)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }

    printf("\n========================================\n");
    fflush(stdout);

    return;
}

int main(int argc, char ** argv)
{
    const unsigned int size = 50;
    randgen_t generator;

    generator.seed(clock());

    int a[size];
    int b[size];
    int c[size];

    RandInit(generator, size, a);
    RandInit(generator, size, b);

    Print(size, a);
    Print(size, b);

    // parallelize
    for (int i = 0; i < size; ++i)
    {
        c[i] = a[i] * b[i];
    }

    Print(size, c);

    return 0;
}

