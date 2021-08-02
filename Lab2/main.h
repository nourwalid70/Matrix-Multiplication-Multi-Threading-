#ifndef MATRIXMULTIPLICATION_H
#define MATRIXMULTIPLICATION_H

#include "ReadFromFile.h"
#include <time.h>
#include <pthread.h>

typedef struct {
    double elapsedT;
    int count;
    int row;
    int col;
    int **data;
} matrixResult;
typedef struct _thread_data_t {
    int tid;
    int i; //row in matrix A
    int j; // column in matrix B
    matrixes * m; // contain matix A and matrix  and their dimansions
    matrixResult* result; //  result of multiplication C[A.rows][B.columns]
} thread_data_t;

typedef struct {
    matrixResult* method1;
    matrixResult* method2;
    matrixResult* method3;
} Results;

void *matrixMethod(void *arg);
void *rowMethod(void *arg);
void *elementMethod(void *arg);

Results * matrixMultiplication(matrixes * data);
matrixResult* intializeMR (matrixes * m);

#endif
