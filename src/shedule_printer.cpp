#include <iostream>

#include "habit.h"
#include "updater.h"

void clear()
{
    std::cout << "\033[2J\033[1;1H" << std::flush;
    // #ifdef _WIN32
    //     std::system("cls");
    // #else
    //     std::system("clear");
    // #endif
}

void wait_input()
{
    std::cout << "Нажмите Enter чтобы продолжить: ";
    std::cin.ignore();
    std::cin.get();
}

void showSchedule()
{
    clear();

    const char* day_names[7]{"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    
    std::cout << "============ РАСПИСАНИЕ НА НЕДЕЛЮ ============\n\n";
    
    for (int i{}; i < 7; i++)
    {
        int cur_wday{get_weekday()};
        if(i == cur_wday)
            std::cout << "<<(" << day_names[i] << ")>>" << ":\n";
        else
            std::cout << day_names[i] << ":\n";

        int has_habits{};
        
        for (int j{}; j < habit_count; j++)
        {
            if (habits[j].days[i] == 1)
            {
                std::cout << "  - " << habits[j].name;
                
                if (habits[j].is_boolean)
                    std::cout << ((habits[j].completed[i]) ? " [✓]" : " [ ]");
                else 
                    std::cout << " [" << habits[j].current_value[i] << "/" << habits[j].target_value << "]";
                
                std::cout << "\n";
                has_habits = 1;
            }
        }
        
        if (!has_habits)
            std::cout << "  Нет привычек\n";

        std::cout << "\n";
    }

    wait_input();
}