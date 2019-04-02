#include <stdio.h>

int main()
{
    const size_t N = 100000;
    double step;

    double x, pi, sum = 0.;

    step = 1. / (double)N;

    for (int i = 0; i < N; ++i)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1. + x * x);
    }

    pi = step * sum;

    printf("pi = %.16f\n", pi);

    return 0;
}
