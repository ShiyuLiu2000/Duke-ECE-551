#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct _IntMatrix_t {
  size_t nRow;
  size_t nCol;
  int ** mat;
};
typedef struct _IntMatrix_t IntMatrix_t;

// Function doing matrix multiplication: A*B
IntMatrix_t * matMult(IntMatrix_t * A, IntMatrix_t * B) {
  // check NULL
  if (A == NULL || B == NULL) {
    return NULL;
  }

  // check dimension
  if (A->nRow == 0 || A->nCol == 0 || B->nRow == 0 || B->nCol == 0) {
    return NULL;
  }
  if (A->nCol != B->nRow) {
    // perror("Unable to perform multiplication!\n");
    return NULL;
  }

  // begin multiplying
  IntMatrix_t * C = malloc(sizeof(*C));
  C->nRow = A->nRow;
  C->nCol = B->nCol;
  C->mat = malloc(C->nRow * sizeof(*C->mat));
  for (size_t i = 0; i < C->nRow; i++) {
    C->mat[i] = malloc(C->nCol * sizeof(*C->mat[i]));
    for (size_t j = 0; j < C->nCol; j++) {
      C->mat[i][j] = 0;
      for (size_t k = 0; k < A->nCol; k++) {
        C->mat[i][j] += A->mat[i][k] * B->mat[k][j];
      }
    }
  }
  return C;
}

// Free a matrix
void freeMat(IntMatrix_t * matrix) {
  if (matrix == NULL) {
    return;
  }
  if (matrix->mat != NULL) {
    for (size_t i = 0; i < matrix->nRow; i++) {
      free(matrix->mat[i]);
    }
  }
  free(matrix->mat);
  free(matrix);
}

// Print a matrix
void printMat(IntMatrix_t * matrix) {
  if (matrix == NULL) {
    perror("Null pointer when printing matrix!\n");
    return;
  }
  for (size_t i = 0; i < matrix->nRow; i++) {
    for (size_t j = 0; j < matrix->nCol; j++) {
      printf("%d", matrix->mat[i][j]);
      if (j != matrix->nCol - 1) {
        printf(" ");
      }
    }
    printf("\n");
  }
}

// Parse one value from a line, helper function for reading matrix
int parseOneValue(char * line, ssize_t len) {
  if (line == NULL || len == -1) {
    perror("Error when reading one value!\n");
    return 0;
  }
  char * num_start = line;
  char * delim = NULL;
  errno = 0;
  if (errno != 0) {
    perror("Error when reading numbers!\n");
    return 0;
  }
  int num = strtol(num_start, &delim, 10);
  return num;
}

// Parse multiple values from a line, helper function for reading matrix
int * parseValues(char * line, ssize_t len, size_t count) {
  if (line == NULL || len == -1) {
    perror("Error when reading multiple values!\n");
    return NULL;
  }

  int * values = malloc(count * sizeof(*values));
  char * num_start = line;
  char * delim = NULL;
  for (size_t i = 0; i < count; i++) {
    errno = 0;
    values[i] = strtol(num_start, &delim, 10);
    if (errno != 0) {
      perror("Error when reading numbers!\n");
      free(values);
      return NULL;
    }
    num_start = delim + 1;
  }
  return values;
}

// Read a matrix from a file
IntMatrix_t * readMat(char * file_name) {
  FILE * f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to open file %s!\n", file_name);
    return NULL;
  }

  // read nRow and nCol
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = getline(&line, &sz, f);
  size_t nRow = parseOneValue(line, len);
  len = getline(&line, &sz, f);
  size_t nCol = parseOneValue(line, len);
  if (nRow == 0 || nCol == 0) {
    free(line);
    return NULL;
  }

  // read matrix
  IntMatrix_t * matrix = malloc(sizeof(*matrix));
  matrix->nRow = nRow;
  matrix->nCol = nCol;
  matrix->mat = malloc(matrix->nRow * sizeof(*matrix->mat));
  for (size_t i = 0; i < matrix->nRow; i++) {
    matrix->mat[i] = NULL;
  }
  for (size_t i = 0; i < matrix->nRow; i++) {
    len = getline(&line, &sz, f);
    matrix->mat[i] = parseValues(line, len, matrix->nCol);
    if (matrix->mat[i] == NULL) {
      perror("Error when reading matrix!\n");
      free(line);
      freeMat(matrix);
      return NULL;
    }
  }
  fclose(f);
  free(line);
  return matrix;
}

int main(void) {
  // read matrices
  size_t nMat = 3;
  IntMatrix_t * mats[nMat];
  mats[0] = readMat("mat0.txt");
  mats[1] = readMat("mat1.txt");
  mats[2] = readMat("mat2.txt");
  printf("M0:\n");
  printMat(mats[0]);
  printf("M1:\n");
  printMat(mats[1]);
  printf("M2:\n");
  printMat(mats[2]);

  // do multiplication
  IntMatrix_t * ans = NULL;
  for (size_t i = 0; i < nMat; i++) {
    for (size_t j = 0; j < nMat; j++) {
      printf("M%lu*M%lu:\n", i, j);
      ans = matMult(mats[i], mats[j]);
      if (ans == NULL) {
        printf("Unable to perform multiplication!\n");
      }
      else {
        printMat(ans);
        freeMat(ans);
        ans = NULL;
      }
    }
  }

  // free matrices
  for (size_t i = 0; i < nMat; i++) {
    freeMat(mats[i]);
  }

  return EXIT_SUCCESS;
}
