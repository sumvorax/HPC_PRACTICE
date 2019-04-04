#include <stdio.h>
#include <stdlib.h>
#include <random>

/// Simlest Schelling model cellular automaton

/// Compile with 'g++ Schelling.c -o schelling.out'
/// Run with './schelling.out'

struct House
{
    // int row;
    // int col;
    int status;
};

// basicly -- square matrix
class City
{
        // linear size of square City
        int size;

        // all houses row-wise
        House * houses;

        // coefficient from [0., 1.]
        double coeff;

        // indices of housed whose inhabitants need to move
        int * wantmove;

    public:

        City();

         // random initialization of houses
        City(const int newsize, const double newcoeff);

        ~City();

        // sets house[k].moveflag if inhabitants of k-th house want to relocate
        // returns number of moveflags set
        int EvaluateMove();
        void Swap(const int first_ind, const int sec_ind);
        void Shuffle(const int count);
        void Iterate(const int iterations);

        // Your I/O
        void FileDump(const int iteration);
};

City::City()
{
    size = 0;
    houses = NULL;
    coeff = 0.;
    wantmove = NULL;

    return;
}

City::City(const int newsize, const double newcoeff)
{
    size = newsize;
    houses = (House *)malloc(size * size * sizeof(House));

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 1);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // houses[i * size + j].row = i;
            // houses[i * size + j].col = j;
            houses[i * size + j].status = distribution(generator);
        }
    }

    coeff = newcoeff;
    wantmove = (int *)malloc(size * size * sizeof(int));

    return;
}

City::~City()
{
    if (houses)
    {
        free(houses);
    }

    if (wantmove)
    {
        free(wantmove);
    }

    return;
}

int City::EvaluateMove()
{
    int count = 0;
    int vicinity_status;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // check status of all neighbours
            vicinity_status = 0;

            if (i > 0)
            {
                vicinity_status += houses[(i - 1) * size + j].status;

                if (j > 0)
                {
                    vicinity_status += houses[(i - 1) * size + j - 1].status;
                }

                if (j < size - 1)
                {
                    vicinity_status += houses[(i - 1) * size + j + 1].status;
                }
            }

            if (i < size - 1)
            {
                vicinity_status += houses[(i + 1) * size + j].status;

                if (j > 0)
                {
                    vicinity_status += houses[(i + 1) * size + j - 1].status;
                }

                if (j < size - 1)
                {
                    vicinity_status += houses[(i + 1) * size + j + 1].status;
                }
            }

            if (j > 0) { vicinity_status += houses[i * size + j - 1].status; }

            if (j < size - 1)
            {
                vicinity_status += houses[i * size + j + 1].status;
            }

            // if average neighbour status is more then coeff -- need to move
            // set 1 if want to move, 0 otherwise
            
            // update wantmove list and total count of houses "need to move"
            if (double(vicinity_status) >= 8 * coeff)
            {
                wantmove[count] = i * size + j;
                ++count;
            }
        }
    }

    return count;
}

// swap statuses
void City::Swap(const int first_ind, const int sec_ind)
{
    int tmp = houses[wantmove[first_ind]].status;
    houses[wantmove[first_ind]].status = houses[wantmove[sec_ind]].status;
    houses[wantmove[sec_ind]].status = tmp;

    return;
}

// Fisher-Yates shuffle
void City::Shuffle(const int count)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, count - 1);

    for (int k = 0; k < count; ++k)
    {
        Swap(k, distribution(generator));
    }

    return;
}

void City::Iterate(const int iterations)
{
    int count;

    for (int k = 0; k < iterations; ++k)
    {
        count = EvaluateMove();
        Shuffle(count);

        FileDump(k);
    }

    return;
}

void City::FileDump(const int iteration)
{
    char buffer[32]; // The filename buffer.
    snprintf(buffer, sizeof(char) * 32, "dump_%d.bin", iteration);

    FILE * file = fopen(buffer, "wb");
    int count = size * size;

    fwrite(&count, sizeof(int), 1, file);

    for (int k = 0; k < count; ++k)
    {
        fwrite(houses + k, sizeof(int), 1, file);
    }

    fclose(file);

    return;
}

int main(int argc, char ** argv)
{
    const int size = 100;
    const double coeff = .51;
    const int iter = 10;

    City city(size, coeff);

    city.Iterate(iter);

    return 0;
}
