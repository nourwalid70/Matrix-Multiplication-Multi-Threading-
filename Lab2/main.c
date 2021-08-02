#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ReadFromFile.h"
#include "main.h"
#include "WriteInFile.h"

// method 1
 void *matrixMethod(void *arg){
        thread_data_t *data = (thread_data_t *) arg;
        int sum=0;
        for (int i = 0; i < data->m->A->rows; i++) {
         for (int j = 0; j < data->m->B->cols; j++) {
           for (int k = 0; k < data->m->B->rows; k++) {
             sum += data->m->A->data[i][k] * data->m->B->data[k][j];
        }
        data->result->data[i][j] = sum;
        sum = 0;
      }
    }
}
// method 2
void *rowMethod(void *arg) {
    thread_data_t *data = (thread_data_t *) arg;
    int row = data->i;
    for (int j = 0; j< data->m->B->cols ; j++){
        int sum = 0;
        for (int i = 0; i < data->m->A->cols ; i++) {
            sum += data->m->A->data[row][i]* data->m->B->data[i][j];
        }
        data->result->data[row][j] = sum;
    }
    pthread_exit(NULL);
}

// method 3
void *elementMethod(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    // element >> c[i]c[j]
    int col = data->j;
    int row = data->i;
    int sum = 0;
    for (int k =0; k < data->m->A->cols; k++) {
        sum += data->m->A->data[row][k] * data->m->B->data[k][col];
    }
    data ->result->data[row][col] = sum;
    pthread_exit(NULL);
}

Results* matrixfinalResulttiplication(matrixes * m){

    if (m->A->cols == m->B->rows) {

     /* create a thread_data_t argument array */
        matrixResult *res1 = intializeMR(m);
        pthread_t thr1[1];
        thread_data_t thr_data1[1];

        matrixResult *res2 = intializeMR(m);
        pthread_t thr2[m->A->rows];
        thread_data_t thr_data2[m->A->rows];

        matrixResult *res3 = intializeMR(m);
        pthread_t thr[m->A->rows][m->B->cols];
        thread_data_t thr_data[m->A->rows][m->B->cols];

        int i;
        clock_t t1, t2;

        // method 1
        t1 = clock(); // initial time
        /* create threads */
            thr_data1[0].result = res1;
            thr_data1[0].m = m;
            pthread_create(&thr1[0], NULL, matrixMethod, &thr_data1[0]);

        /* block until all threads complete */
            pthread_join(thr1[0], NULL);
        t2 = clock(); // finish time
        res1->elapsedT = t2 - t1;
        res1->count = 1;


        // method 2
        t1 = clock(); // initial time
        /* create threads */
        for (i = 0; i < m->A->rows; ++i) {
            thr_data2[i].tid = i;
            thr_data2[i].i = i; //a row
            thr_data2[i].j = 0; //b cloumn
            thr_data2[i].result = res2;
            thr_data2[i].m = m;
            pthread_create(&thr2[i], NULL, rowMethod, &thr_data2[i]);
        }
        /* block until all threads complete */
        for (i = 0; i < m->A->rows; ++i) {
            pthread_join(thr2[i], NULL);
        }
        t2 = clock(); // finish time
        res2->elapsedT = t2 - t1;
        res2->count = m->A->rows;

        // method 3
        t1 = clock(); // initial time
        /* create threads */
        for (i = 0; i < m->A->rows; ++i) {
            for (int j = 0; j < m->B->cols; ++j) {
                thr_data[i][j].tid = i + j;
                thr_data[i][j].i = i; //a row
                thr_data[i][j].j = j; //b cloumn
                thr_data[i][j].result = res3;
                thr_data[i][j].m = m;
                pthread_create(&thr[i][j], NULL, elementMethod, &thr_data[i][j]);
            }
        }
        /* block until all threads complete */
        for (i = 0; i < m->A->rows; ++i) {
            for (int j = 0; j < m->B->cols; ++j) {
                pthread_join(thr[i][j], NULL);
            }
        }
        t2 = clock(); // finish time
        res3->elapsedT = t2 - t1;
        res3->count = m->A->rows*m->B->cols;

        Results *r = (Results *) malloc(sizeof(Results));
        r->method1 = res1;
        r->method2 = res2;
        r->method3 = res3;

        return r;

    }else{
        printf("Invalid Dimaensions\n");
        exit(1);
    }
}
  matrixResult* intializeMR (matrixes * m) {
    matrixResult * res3 =(matrixResult *) malloc(sizeof(matrixResult)); //contain the result of element method
    // allocate a int array of length rows * cols
    res3 ->col = m->B->cols;
    res3->row = m->A->rows;
    res3->data = malloc(res3->row * sizeof(int*));
    if(res3->data == NULL) {
        printf("Out of memory\n");
        exit(1);
    }
    for(int i = 0; i < res3->row; i++) {
        res3->data[i] = malloc(res3->col * sizeof(int));
        if(res3->data[i] == NULL) {
            printf("Out of memory\n");
            exit(1);
        }
    }
    return res3;
}
int main(int argc, char **argv) {
        if(argc == 1){
            matrixes * data  = readMatrixes("Mat1.txt","Mat2.txt"); // read from files
            Results* finalResult = matrixfinalResulttiplication(data); // finalResulttiplication
            matrixOutPutFile("MatOut.txt", finalResult); // write in file
        }
        else if(argc == 4){
                char s1[20];
                char s2[20];
                char s3[20];
                strcpy( s1, argv[1]);
                strcat( s1, ".txt"); // mat1
                strcpy( s2, argv[2]);
                strcat( s2, ".txt"); // mat2
                strcpy( s3, argv[3]);
                strcat( s3, ".txt"); // mat1Out

            matrixes * data  = readMatrixes(s1,s2); // read from files
            Results* finalResult = matrixfinalResulttiplication(data); // finalResulttiplication
            matrixOutPutFile(s3, finalResult); // write in file
        }
        else{
            printf("Invalid input!\n");
        }
}
