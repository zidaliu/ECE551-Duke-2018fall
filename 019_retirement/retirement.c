#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

double work_retire(int startAge, int Num_month, double total_money, retire_info_t info) {
  for (int i = 0; i < Num_month; i++) {
    int this_year = (startAge + i) / 12;
    int this_month = (startAge + i) % 12;
    printf("Age %3d month %2d you have $%.2lf\n", this_year, this_month, total_money);
    total_money = total_money * (1 + info.rate_of_return) + info.contribution;
  }
  return total_money;
}

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  int Num_month_work = working.months;
  int Num_month_retire = retired.months;
  double total_money = initial;
  total_money = work_retire(startAge, Num_month_work, total_money, working);
  work_retire(startAge + working.months, Num_month_retire, total_money, retired);
}

int main(void) {
  retire_info_t working;
  retire_info_t retire;
  working.months = 489;
  working.rate_of_return = 0.045 / 12;
  working.contribution = 1000;
  retire.months = 384;
  retire.rate_of_return = 0.01 / 12;
  retire.contribution = -4000;
  int starage = 327;
  double saving = 21345;
  retirement(starage, saving, working, retire);
  return 0;
}
