#include <cstdio>
#include <cmath>
#include <ctime>

#include <iostream>
using namespace std;

double func(double a, int b = 3) {
    return pow(a, b);
}

int main(int argc, char** argv) {
    
    int a, b;           // function bounders
    double min, max;    // min and max of function
    int stepN;          // count of steps for calculate function min and max
    int amountOfDot;    // how many dot we throw on graphic

    FILE *infile = fopen("input.txt", "r");

    if (infile == NULL) {
        printf("File reading error. Try to relocate input file\n");
        exit(0);
    }

    fscanf(infile, "a=%d\n", &a);
    fscanf(infile, "b=%d\n", &b);
    fscanf(infile, "stepN=%d\n", &stepN);
    fscanf(infile, "amountOfDot=%d\n", &amountOfDot);
    printf("a=%d, b=%d, stepM=%d, amountofDot=%d\n", a, b, stepN, amountOfDot);

    //  In this block we find min and max of function
    double stepSize = (double)(abs(a) + abs(b)) / stepN;
   
    min = max = func(a);
    for (double i = a; i <= b; i+=stepSize) {
        double res = func(i);
        if (res > max)
            max = res;
        else if (res < min)
            min = res;
    }
    cout << min << " " << max << endl;

    srand(time(0));
    //  We throw a random dot in field step by step 
    double stepSizeThrow = (double)(abs(a) + abs(b)) / amountOfDot;
    int dotInField = 0;     // Amount of dot in our area (under integral)
    for (double i = a; i <= b; i += stepSizeThrow) {
        //double randPoint = rand() % ((int)(max - min) + 1);     // we must also include the bounders 
        double randPoint = (double)(rand()) / RAND_MAX * (max - min);
                                                                // for example, if max(3) - min(1) = rand % 2, (0,1) but min+1 != max
                                                                // Warning! If max - min > 32767 (RAND_MAX) we have a problem
        randPoint += min;                                       // result of rand should be in range between max and min
        if (randPoint <= func(i)) {
            dotInField++;
        }
    }

    // After all, we know amount of throwing dots, and can calculate square under function
    double areaSquare = (b - a) * (max - min);  //  square of our area
    double resultIntegral = areaSquare * dotInField / amountOfDot;
    printf("%lf\n", resultIntegral);
    system("pause");
    return 0;
}
