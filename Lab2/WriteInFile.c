#include "WriteInFile.h"

void matrixOutPutFile(char* fileName,  Results* finalResult) {
    remove(fileName);
    FILE *out_file = fopen(fileName, "a"); // write mode
    // test for files not existing.
    if (out_file == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }
    //method 1
    fprintf(out_file, "\t\t\t\tMethod1\n");
    fprintf(out_file, "row=%d col=%d\n", finalResult->method1->row, finalResult->method1->col); // write to file
    for(int i = 0; i < finalResult->method1->row; ++i ){
        for(int j = 0; j < finalResult->method1->col -1; ++j) {
            fprintf(out_file, "%d\t", finalResult->method1->data[i][j]);
        }
        fprintf(out_file, "%d\n", finalResult->method1->data[i][finalResult-> method1->col -1]);
    }
    printf("# Threads in method1 =\t%d\n",finalResult->method1->count);
    printf("Time of method1\t%lf\n",finalResult->method1->elapsedT); // write to file


    //method 2
    fprintf(out_file, "\n\t\t\t\tMethod2\n");
    fprintf(out_file, "row=%d col=%d\n", finalResult->method2->row, finalResult->method2->col); // write to file
    for(int i = 0; i < finalResult->method2->row; ++i ){
        for(int j = 0; j < finalResult->method2->col -1; ++j) {
            fprintf(out_file, "%d\t", finalResult->method2->data[i][j]);
        }
        fprintf(out_file, "%d\n", finalResult->method2->data[i][finalResult-> method2->col -1]);
    }
   printf("# Threads in method2 =\t%d\n",finalResult->method2->count);
   printf("Time of method2\t%lf\n",finalResult->method2->elapsedT); // write to file


     //method 3
     fprintf(out_file, "\n\t\t\t\tMethod3\n");
     fprintf(out_file, "row=%d col=%d\n", finalResult->method3->row, finalResult->method3->col); // write to file
     for(int i = 0; i < finalResult->method3->row; ++i ){
        for(int j = 0; j < finalResult->method3->col -1; ++j) {
            fprintf(out_file, "%d\t", finalResult->method3->data[i][j]);
        }
        fprintf(out_file, "%d\n", finalResult->method3->data[i][finalResult-> method3->col -1]);
    }
     printf("# Threads in method3 =\t%d\n",finalResult->method3->count);
     printf("Time of method3\t%lf\n",finalResult->method3->elapsedT); // write to file


    fclose(out_file);

}
