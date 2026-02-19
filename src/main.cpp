#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>

#include "habit.h"

Habit habits[MAX_HABITS];
int habit_count = 0;
const char* fileName = "habits_data.txt";

#include "file_mgr.h"
#include "habit_mgr.h"
#include "updater.h"
#include "shedule_printer.h"

int main()
{
    loadFromFile();
    
    int choice{};
    do 
    {
        std::cout << "\033[2J\033[1;1H"; // Для очищения консоли
        std::cout << "\n===== ТРЕКЕР ПРИВЫЧЕК =====\n";
        std::cout << "1. Добавить привычку\n";
        std::cout << "2. Удалить привычку\n";
        std::cout << "3. Показать расписание\n";
        std::cout << "4. Обновить прогресс\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (std::cin.fail() || (std::cin.peek() != '\n') || ((choice < 0) || (choice > 5)))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else
        {
            switch (choice)
            {
                case 1:
                    addHabit();
                    break;
                case 2:
                    removeHabit();
                    break;
                case 3:
                    showSchedule();
                    break;
                case 4:
                    updateProgress();
                    break;
                case 5:
                    std::cout << "До свидания!\n";
                    break;
                default:
                    std::cout << "Неверный выбор\n";
                    wait_input();
            }
        }
    } while (choice != 5);
    
    return 0;
}