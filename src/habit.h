#pragma once

const int MAX_HABITS = 50;
const int NAME_LEN = 50;

struct Habit
{
    char name[NAME_LEN];
    bool is_boolean;          // true - да/нет, false - число
    int target_value;          // целевое значение (для числовых)
    int current_value[7];      // текущее значение по дням
    int completed[7];          // выполнено/нет по дням
    int days[7];               // выбранные дни
};

extern Habit habits[MAX_HABITS];
extern int habit_count;
extern const char* fileName;