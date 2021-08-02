#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int rows;
    int cols;
    int **data;
} matrix;
typedef struct {
    int n;
    int *data;
} arr;

typedef struct {
     matrix* A;
     matrix* B;
} matrixes;

matrix * newMatrix(int rows, int cols, FILE *fp);
matrixes * readMatrixes(char *fileName1,char *fileName2);

#endif
