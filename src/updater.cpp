#include <iostream>
#include <ctime>

#include "habit.h"
#include "shedule_printer.h"
#include "file_mgr.h"

int get_weekday()
{
    std::time_t t{std::time(nullptr)};
    int wday{std::localtime(&t)->tm_wday};
    
    return (wday == 0) ? 6 : wday-1;
}

void updateProgress()
{
    clear();
    if (habit_count == 0)
    {
        std::cout << "Список привычек пуст\n";
        wait_input();
        return;
    }
    
    for (int i{}; i < habit_count; i++)                     // По идее тут должна быть проверка есть ли привычка сегодня для того чтобы решаить отображать ее или нет.
        std::cout << i + 1 << ". " << habits[i].name << "\n";
    
    int cur_wday{get_weekday()};
    int index{};
    std::cout << "Выберите привычку: ";

    while(true)
    {
        std::cin >> index;
        if (std::cin.fail() || (std::cin.peek() != '\n') || ((index < 0) || (index > habit_count)))
        {
            std::cout << "Введено некорректное значение!\nВведите номер привычки из списка: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else break;
    }
        
    Habit& h{habits[index - 1]};

    if(!h.days[cur_wday])
    {
        std::cout << "На сегодня нет этой привычки" << "\n";
        wait_input();
        return;
    }
    
    if (h.is_boolean) 
    {
        std::cout << "Выполнено? (1 - да, 0 - нет): ";
        int input{};

        while(true) // Проверка на корректность ввода
        {
            std::cin >> input;
            if(std::cin.fail() || (std::cin.peek() != '\n') || ((input != 1) && (input != 0)))
            {
                std::cout << "Введено некорректное значение!\nВведите 0 или 1: ";
                std::cin.clear(); // Сброс флага ошибки
                std::cin.ignore(10000, '\n'); // Очистка буфера от мусора
            }
            else
            {
                h.completed[cur_wday] = (input == 1) ? 1 : 0;
                break;
            } 
        }   
    }
    else 
    {
        std::cout << "Введите текущее значение: ";
        int input{};

        while(true) // Проверка на корректность ввода
        {
            std::cin >> input;
            if(std::cin.fail() || (std::cin.peek() != '\n') || (input < 0))
            {
                std::cout << "Введено некорректное значение!\nВведите целое число больше нуля: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else
            {
                h.current_value[cur_wday] = input;
                break;
            } 
        }                
        
        if (h.current_value[cur_wday] >= h.target_value)
        {
            h.completed[cur_wday] = 1;
            std::cout << "Цель достигнута!\n";
        }
    }
        saveToFile();
        std::cout << "Прогресс обновлен!\n";
        wait_input();
}