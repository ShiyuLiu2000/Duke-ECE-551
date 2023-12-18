#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

void print_message(int age, int month, double balance) {
  printf("Age %3d month %2d you have $%.2f\n", age, month, balance);
}

typedef struct _retire_info retire_info;

double information(int startAge, double initial, retire_info status) {
  int month = startAge % 12;
  startAge /= 12;
  double increase = 0.0;
  int i = 0;
  if (status.contribution < 0) {
    i = 1;
  }
  while (i <= status.months) {
    initial += increase;
    if ((i != 1) || (status.contribution > 0)) {
      print_message(startAge, month, initial);
    }
    if (month == 11) {
      month = 0;
      startAge += 1;
    }
    else {
      month += 1;
    }
    increase = status.contribution + initial * status.rate_of_return;
    i++;
  }
  return initial;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = information(startAge, initial, working);
  information(working.months + startAge, balance, retired);
}

int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
