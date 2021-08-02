#include "ReadFromFile.h"

/* Creates a ``rows by cols'' matrix with all values 0.
 * Returns NULL if rows <= 0 or cols <= 0 and otherwise a
 * pointer to the new matrix.
 */
matrix * newMatrix(int rows, int cols, FILE *fp) {
    if (rows <= 0 || cols <= 0)
        return NULL;

    matrix * m = (matrix *) malloc(sizeof(matrix));  // allocate a matrix

    // set dimensions
    m->rows = rows;
    m->cols = cols;

    m->data = malloc(rows * sizeof(int*));   // allocate a double array of length rows * cols
    if(m->data == NULL) {
        printf("Out of memory\n");
        exit(1);
    }

    for(int i = 0; i < rows; i++) {
        m->data[i] = malloc(cols * sizeof(int));
        if(m->data[i] == NULL) {
            printf("Out of memory\n");
            exit(1);
        }
    }

// Read matrix content from file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int n;
            fscanf(fp, "%d", &n);
            m->data[i][j] = n;
        }
    }

    return m;
}
matrixes* readMatrixes(char *fileName1,char *fileName2){

    FILE *fp1,*fp2;
    fp1 = fopen(fileName1, "r");  // read mode
    fp2 = fopen(fileName2, "r"); // read mode

    if(fp1 == NULL || fp2 == NULL){
          printf("file could not be opened So open the default files\n");
          fp1 = fopen("Mat1.txt", "r");  // read mode
          fp2 = fopen("Mat2.txt", "r"); // read mode
          matrixes * data = (matrixes *) malloc(sizeof(matrixes));
          int m,n;
         printf("file1 is opened\n");
         fscanf(fp1,"%d %d",&m,&n);
         data->A = newMatrix(m,n,fp1);
         fclose(fp1);

         printf("file2 is opened\n");
         fscanf(fp2,"%d %d \n",&m,&n);
         data->B = newMatrix(m,n,fp2);
         fclose(fp2);
            return data;
      }
      else{
            matrixes * data = (matrixes *) malloc(sizeof(matrixes));
            int m,n;
            printf("file1 is opened\n");
            fscanf(fp1,"%d %d",&m,&n);
            data->A = newMatrix(m,n,fp1);
            fclose(fp1);

            printf("file2 is opened\n");
            fscanf(fp2,"%d %d \n",&m,&n);
            data->B = newMatrix(m,n,fp2);
            fclose(fp2);
                return data;
      }
}
