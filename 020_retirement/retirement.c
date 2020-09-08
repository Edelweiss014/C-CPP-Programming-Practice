#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculate_new (retire_info work_or_retire, double saving) {
  saving += work_or_retire.rate_of_return * saving;
  saving += work_or_retire.contribution;
  return saving;
}

void retirement (int startAge,
		 double initial,
		 retire_info working,
		 retire_info retired) {
  double saving = initial;
  int age = startAge / 12;
  int month_after_age = startAge % 12;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", age, month_after_age, saving);
    saving = calculate_new(working, saving);
    if (month_after_age == 11) {
      age++;
      month_after_age = 0;
    }
    else {
      month_after_age++;
    }
  }
  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", age, month_after_age, saving);
    saving = calculate_new(retired, saving);
    if (month_after_age == 11) {
      age++;
      month_after_age = 0;
    }
    else {
      month_after_age++;
    }
  }
  return;
}

int main (){

  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;
  retire_info retired;
  retired.months = 384; 
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  double initial = 21345;
  int startAge = 327;
  retirement(startAge, initial, working, retired);
  
  return 0;
}
