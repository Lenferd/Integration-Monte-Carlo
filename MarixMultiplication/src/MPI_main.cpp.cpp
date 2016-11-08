//
// Created by lenferd on 25.10.16.
//

#include <cstdio>
#include <mpi.h>
#include <cstdlib>
#include <iostream>

using std::string;

void fillMatrix(double* &matrix, string filename, int &size) {
    FILE *infile = fopen(filename.c_str(), "r");

    if (infile == NULL) {
        printf("File reading error. Try to relocate input file\n");
        exit(0);
    }

    // Scan size of matrix.
    fscanf(infile, "size=%d", &size);
    if (size == 0 || size < 0) {
        printf("Error, wrong size");
        exit(0);
    }

    matrix = new double[size*size];
    for (int i = 0; i < size * size; ++i) {
        fscanf(infile, "%lf", &matrix[i]);
    }
    fclose(infile);
}

void calculateResult(double* &matrixA, double* &matrixB, double* &matrixC, int &size, int &proc_size) {
    matrixC = new double[size*size];
    for (int i = 0; i < size * size; ++i) {
        matrixC[i] = 0;
    }

    int proc_rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &proc_rank); /* get current process id */

    int local_size = 0; // How many vectors have

    if (proc_rank == 0) {
        if ((size / proc_size) * 10 % 10 > 0 || size / proc_size < 1) {
            printf("Error, wrong matrix size or proc count");
            exit(0);
        } else {
            local_size = size / proc_size;
        }
    }
    MPI_Bcast(&local_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    double* bufA = new double[local_size*size];
    double* bufC = new double[local_size*size];
    int part = local_size * size;

    MPI_Scatter(matrixA, part, MPI_DOUBLE, bufA, part, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_size; ++i) {
        for (int j = 0; j < size; ++j)
            for (int k = 0; k < size; ++k) {
                bufC[i*size + j] += bufA[i*size + k] * matrixB[k*size +j];
            }
    }

    /*for (int i = proc_rank*local_size; i < (proc_rank+1) * local_size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                matrixC[i*size+j] += matrixA[i*size+k] * matrixB[k*size+j];
            }
        }
    }*/

    MPI_Gather(bufC, local_size*size, MPI_DOUBLE, matrixC, local_size*size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
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
    double* aMatrix = nullptr;
    double* bMatrix = nullptr;
    double* cMatrix = nullptr;
    int vector_size;
    int vector_size2;

    int proc_size;
    int proc_rank;

    double startTime, endTime = 0.0; // program working time

    string fileA = "InputA.txt";
    string fileB = "InputB.txt";
    string fileC = "MPI_OutputC.txt";

    MPI_Init (&argc, &argv); /* starts MPI */
    MPI_Comm_rank (MPI_COMM_WORLD, &proc_rank); /* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &proc_size); /* get number of processes */

    if (proc_rank == 0) {
        fillMatrix(aMatrix, fileA, vector_size);
        fillMatrix(bMatrix, fileB, vector_size2);

        if (vector_size != vector_size2) {
            printf("Error, file have not equal dimension");
            exit(0);
        }
    }
    MPI_Bcast(&vector_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (proc_rank != 0) {
        aMatrix = new double[vector_size*vector_size];
        bMatrix = new double[vector_size*vector_size];
    }
    MPI_Bcast(aMatrix, vector_size*vector_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(bMatrix, vector_size*vector_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    startTime = MPI_Wtime();
    calculateResult(aMatrix, bMatrix, cMatrix, vector_size, proc_size);
    endTime = MPI_Wtime();

    if (proc_rank == 0) {
        printMatrix(cMatrix, fileC, vector_size);
        printf("Working time = %.6f, amount of process = %d\n", endTime - startTime, proc_size);
    }

    MPI_Finalize();
    return 0;
}