//
// Created by lenferd on 25.10.16.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>

using std::string;

void fillMatrix(double* &matrix, string filename, int &size) {
    FILE *infile = fopen(filename.c_str(), "r");

    if (infile == NULL) {
        printf("File reading error. Try to relocate input file\n");
        exit(0);
    }

    // Scan size of matrix.
    int returnCode = fscanf(infile, "size=%d\n", &size);
    if (size == 0 || size < 0 || returnCode == 0) {
        printf("Error, wrong size");
        exit(0);
    }

    matrix = new double[size*size];
    for (int i = 0; i < size * size; ++i) {
        returnCode = fscanf(infile, "%lf", &matrix[i]);
    }
    if (returnCode == 0) {
        printf("Error, matrix is not correct");
        exit(0);
    }
    fclose(infile);
}

void calculateResult(double* &matrixA, double* &matrixB, double* &matrixC, int &size) {
    matrixC = new double[size*size];
    for (int i = 0; i < size * size; ++i) {
        matrixC[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                matrixC[i*size+j] += matrixA[i*size+k] * matrixB[k*size+j];
            }
        }
    }
}

void printMatrix(double* &matrix, string filename, int size) {
    FILE *outfile = fopen(filename.c_str(), "w");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(outfile, "%lf\t", matrix[i*size + j]);
        }
        fprintf(outfile, "\n");
    }
}

int main(int argc, char** argv) {

    std::clock_t startTime;
    double* aMatrix = nullptr;
    double* bMatrix = nullptr;
    double* cMatrix = nullptr;
    int size;
    int size2;
    string fileA = "InputA.txt";
    string fileB = "InputB.txt";
    string fileC = "Common_OutputC.txt";

    fillMatrix(aMatrix, fileA, size);
    fillMatrix(bMatrix, fileB, size2);

    if (size != size2) {
        printf("Error, file have not equal dimension");
        exit(0);
    }

    startTime = std::clock();
    calculateResult(aMatrix, bMatrix, cMatrix, size);

    printf("Working time = %.6f\n", ( std::clock() - startTime ) / (double) CLOCKS_PER_SEC);

    printMatrix(cMatrix, fileC, size);
}