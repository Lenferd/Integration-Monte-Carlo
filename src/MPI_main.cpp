//
// Created by lenferd on 11.10.16.
//

#include <mpi.h>
#include <cmath>
#include <ctime>
#include <cstdlib>

// function which calculate
double func(double x, int power = 2) {
    return pow(x, power);
}

int main (int argc, char* argv[]) {

    int rank, size;     // MPI data

    int a, b;           // function bounders
    double min, max;    // min and max of function
    int stepN;          // count of steps for calculate function min and max
    int amountOfDot;    // how many dot we throw on graphic
    int functionPower;  // we use power function in this program
    double dotInField;
    double stepSize;

    MPI_Init (&argc, &argv); /* starts MPI */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &size); /* get number of processes */

    if (rank == 0) {
        FILE *infile = fopen("input.txt", "r");

        if (infile == NULL) {
            printf("File reading error. Try to relocate input file\n");
            exit(0);
        }

        fscanf(infile, "a=%d\n", &a);
        fscanf(infile, "b=%d\n", &b);
        fscanf(infile, "powerOfFunction=%d\n", &functionPower);
        fscanf(infile, "stepN=%d\n", &stepN);
        fscanf(infile, "amountOfDot=%d\n", &amountOfDot);
        printf("a=%d, b=%d, stepM=%d, amountofDot=%d\n", a, b, stepN, amountOfDot);
    }

    MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&functionPower, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&amountOfDot, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&stepN, 1, MPI_INT, 0, MPI_COMM_WORLD);


    //  In this block we find min and max of function
    if (stepN > 1000){
        int bounders_step = stepN / size;
        double local_min, local_max = func(a);
        stepSize = (double)(abs(a) + abs(b)) / stepN;
        double local_bounders_size = bounders_step * stepSize;

        for (double i = a + (rank * local_bounders_size); i <= a + (rank + 1) * local_bounders_size; i += stepSize) {
            double res = func(i);
            if (res > max)
                local_max = res;
            else if (res < min)
                local_min = res;
        }

        MPI_Allreduce(&local_min, &min, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
        MPI_Allreduce(&local_max, &max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    } else {
        double stepSize = (double)(abs(a) + abs(b)) / stepN;

        min = max = func(a);
        for (double i = a; i <= b; i+=stepSize) {
            double res = func(i);
            if (res > max)
                max = res;
            else if (res < min)
                min = res;
        }
        MPI_Bcast(&max, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(&min, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    };

    srand(time(0) + rank);
    //  We throw a random dot in field step by step
    double stepSizeThrow = (double)(fabs(a) + fabs(b)) / amountOfDot;
    double local_dotInField = 0;                                         // Amount of dot in our area (under integral)
    double local_step = amountOfDot / size;
    double local_size = stepSizeThrow * local_step;
    for (double i = a + (rank * local_size); i <= a + (rank + 1) * local_size; i+= stepSizeThrow) {
        double randPoint = (double)(rand()) / RAND_MAX * (max - min);   // We throw a random points in our field
        randPoint += min;                                               // result of rand should be in range between max and min
        if (randPoint <= func(i)) {
            local_dotInField++;
        }
    }

    MPI_Reduce(&local_dotInField, &dotInField, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // After all, we know amount of throwing dots, and can calculate square under function
    if (rank == 0) {
        double areaSquare = (b - a) * (max - min);                      //  square of our area
        double resultIntegral = areaSquare * dotInField / amountOfDot;
        printf("Intgral = %lf\n", resultIntegral);
    }

    MPI_Finalize();
    return 0;
}
