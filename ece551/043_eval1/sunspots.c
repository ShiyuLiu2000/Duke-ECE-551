#include "sunspots.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// check if input is a number digit 0-9
int inputIsNumber(char c) {
  int ascii = (int)c;

  // input is a number if the corresponding ascii value ranges from 48 to 57(inclusive)
  if ((ascii >= 48) && (ascii <= 57)) {
    return 1;
  }
  else {
    return 0;
  }
}

// subtring (year or date) of length n to integer, and process input sanitary check
int parseInt(char * str, int n) {
  char tmp[n + 1];

  // all input must be number, else error
  for (size_t i = 0; i < n; i++) {
    if (inputIsNumber(str[i]) == 1) {
      tmp[i] = str[i];
    }
    else {
      fprintf(stderr, "Please enter numbers 0-9 for both YYYY and MM\n");
      exit(EXIT_FAILURE);
    }
  }
  tmp[n] = '\0';

  // perform safe string to int casting
  int ans = atoi(tmp);
  return ans;
}

// string (number of sunspots) to double, and process input sanitary check
double parseDouble(char * str) {
  int dot_counter = 0;

  // all input must be number and could have at most one '.', else error
  char * tmp = str;
  while ((*tmp != '\0') && (*tmp != '\n')) {
    if (*tmp == '.') {
      dot_counter += 1;
    }
    else {
      if (inputIsNumber(*tmp) == 0) {
        fprintf(stderr, "Please only enter numbers 0-9 and dot for number of sunspots\n");
        exit(EXIT_FAILURE);
      }
    }
    tmp += 1;
  }
  if (dot_counter > 1) {
    fprintf(stderr, "Please enter at most one dot for a valid floating number\n");
    exit(EXIT_FAILURE);
  }

  // perform safe string to double casting
  double ans = atof(str);
  return ans;
}

// STEP 1: normalisation of inputs in the form "YYYY-MM,number of sunspots"
ss_monthly_t parseLine(char * line) {
  // check if input meets the minimum form requirement
  if ((line == NULL || *line == '\n')) {
    fprintf(stderr, "Please input date and number of sunspots\n");
    exit(EXIT_FAILURE);
  }
  size_t n = strlen(line);
  if ((n < 9) || (line[4] != '-') || (line[7] != ',')) {
    fprintf(stderr, "Please respect to the input form 'YYYY-MM,number of sunspots'\n");
    exit(EXIT_FAILURE);
  }

  // parse YYYY
  int year = parseInt(line, 4);

  // parse MM
  line += 5;
  int month = parseInt(line, 2);
  if (month == 0 || month >= 13) {
    fprintf(stderr, "Please enter a valid month 01-12\n");
    exit(EXIT_FAILURE);
  }

  // parse number of sunspots
  line += 3;
  double num = parseDouble(line);

  ss_monthly_t ans;
  ans.year = year;
  ans.month = month;
  ans.num = num;
  return ans;
}

// calculate the average float number at data.num place with a given window length: l to its left, and r to its right
double averageWindow(ss_monthly_t * data, unsigned l, unsigned r) {
  double ans = 0;
  ss_monthly_t * tmp = data;
  tmp -= l;
  for (unsigned i = 0; i < l + r + 1; i++) {
    ans += tmp[i].num;
  }
  return ans / (l + r + 1);
}

// STEP 2: mean filter the number of sunspots with window
void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // check if w is valid
  if (w > n) {
    fprintf(stderr, "Window length cannot be larger than array size\n");
    exit(EXIT_FAILURE);
  }

  // initialize year and month in result
  for (size_t i = 0; i < n; i++) {
    mean[i].month = data[i].month;
    mean[i].year = data[i].year;
  }

  // mean filter data close to left boundary
  for (size_t i = 0; i < w / 2; i++) {
    mean[i].num = averageWindow(data + i, i, w / 2);
  }

  // mean filter data in the middle, where whe window can fully stretch
  for (size_t i = w / 2; i < n - w / 2; i++) {
    mean[i].num = averageWindow(data + i, w / 2, w / 2);
  }

  // mean filter data close to right boundary
  for (size_t i = n - w / 2; i < n; i++) {
    mean[i].num = averageWindow(data + i, w / 2, n - 1 - i);
  }
}

// STEP 3: find the timestamp of local maximum sunspots number
double findLocalMax(ss_monthly_t * data, size_t n) {
  // deal with 0 input error case
  if (n == 0) {
    fprintf(stderr, "Please input at least one month data");
    exit(EXIT_FAILURE);
  }

  // initialization
  double max = data->num;
  double time_stamp = data->year + data->month / 12.0;

  // iterate through data array to find the local max
  for (size_t i = 0; i < n; i++) {
    if (data[i].num > max) {
      max = data[i].num;
      time_stamp = data[i].year + data[i].month / 12.0;
    }
  }
  return time_stamp;
}

// STEP 4: calculate the approximate period of sunspots
double calcSsPeriod(double * timeStamps, size_t n) {
  if (n < 2) {
    fprintf(stderr, "Please input at least two timestamps to estimate the period");
    exit(EXIT_FAILURE);
  }

  // calculate and sum the differences
  double ans = 0;
  for (size_t i = 0; i < n - 1; i++) {
    ans += timeStamps[i + 1] - timeStamps[i];
  }

  //calculate the average period
  ans /= n - 1;

  return ans;
}
