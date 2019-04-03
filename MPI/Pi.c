#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// PI number Monte-Carlo calculation
/// TASK: write MPI-reduction with Send-Recv primitives 

int main(int argc, char ** argv)
{
    srand(time(NULL));

    const int N = 100000;

    long int count = 0;
    double x = 0.0;
    double y = 0.0;
    
    for (int i = 0; i < N; ++i)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1.)
        {
            ++count;
        }
    }

    // put reduction here

    printf("PI = %lf\n", 4. * (double)count / N);

    return 0;
}
