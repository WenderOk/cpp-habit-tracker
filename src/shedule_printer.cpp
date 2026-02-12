void showSchedule()
{
    std::cout << "\033[2J\033[1;1H";

    const char* dayNames[7] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    
    std::cout << "============ РАСПИСАНИЕ НА НЕДЕЛЮ ============\n\n";
    
    for (int i{}; i < 7; i++)
    {
        std::cout << dayNames[i] << ":\n";
        int has_habits{};
        
        for (int j{}; j < habit_count; j++)
        {
            if (habits[j].days[i] == 1)
            {
                std::cout << "  - " << habits[j].name;
                std::cout << " (каждые " << habits[j].days_frequency << " дн.)";
                
                if (habits[j].is_boolean)
                {
                    std::cout << " [да/нет]";
                    if (habits[j].completed) std::cout << " (выполнено)";
                }
                else 
                    std::cout << " [" << habits[j].current_value << "/" << habits[j].target_value << "]";
                
                std::cout << "\n";
                has_habits = 1;
            }
        }
        
        if (!has_habits)
            std::cout << "  Нет привычек\n";

        std::cout << "\n";
    }
}