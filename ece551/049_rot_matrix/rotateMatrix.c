#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return 1 if input char is proper, else 0
// proper <==> 10 non-newline characters
int checkValidChar(char c) {
  if (c == '\n') {
    return 1;
  }
  // check ascii for available characters
  if (c < 32 || c > 126) {
    return 0;
  }
  else {
    return 1;
  }
}

// 90 degree clockwise rotation on 10x10 matrix
void rotateMatrix(char ** matrix) {
  // rotate matrix, store rotated value into a new matrix
  char temp[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      temp[j][9 - i] = matrix[i][j];
    }
  }

  // assign rotated value back to matrix, avoid returning a dangling pointer
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = temp[i][j];
    }
  }
}

// print out matrix
void printMatrix(char ** matrix) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("Usage: ./rotateMatrix inputMatrix.txt");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Cannot open file");
    exit(EXIT_FAILURE);
  }

  char row0[11];  // 10 for matrix contents, 1 for \n
  char row1[11];
  char row2[11];
  char row3[11];
  char row4[11];
  char row5[11];
  char row6[11];
  char row7[11];
  char row8[11];
  char row9[11];
  char * matrix[10] = {row0, row1, row2, row3, row4, row5, row6, row7, row8, row9};

  int c;
  int char_count = 0;  // make sure that inputMatrix.txt has exactly 110 chars
  int row = 0;
  int col = 0;
  while ((c = fgetc(f)) != EOF) {
    if (checkValidChar((char)c) == 0) {
      perror("Detected non-valid input characters!");
      exit(EXIT_FAILURE);
    }
    col = char_count % 11;  // toggle matrix [row][col]
    char_count += 1;
    if (char_count > 110) {
      perror("Input file is too long to make a 10x10 matrix");
      exit(EXIT_FAILURE);
    }
    matrix[row][col] = (char)c;
    if (char_count % 11 == 0) {
      // move to next row
      row += 1;
    }
  }

  if (char_count < 110) {
    perror("Input file is not long enough to make a 10x10 matrix");
    exit(EXIT_FAILURE);
  }

  rotateMatrix(matrix);
  printMatrix(matrix);

  return EXIT_SUCCESS;
}
