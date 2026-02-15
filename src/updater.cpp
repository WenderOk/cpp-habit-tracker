int get_weekday() {
    std::time_t t{std::time(nullptr)};
    int wday{std::localtime(&t)->tm_wday};
    
    return (wday == 0) ? 6 : wday;
}

void updateProgress()
{
    std::cout << "\033[2J\033[1;1H";
    if (habit_count == 0)
    {
        std::cout << "Список привычек пуст\n";
        return;
    }
    
    for (int i{}; i < habit_count; i++)                     // По идее тут должна быть проверка есть ли привычка сегодня для того чтобы решаить отображать ее или нет.
        std::cout << i + 1 << ". " << habits[i].name << "\n";
    
    int cur_wday{get_weekday()};
    int index{};
    std::cout << "Выберите привычку: ";
    std::cin >> index;

    if (index > 0 && index <= habit_count)
    {
        Habit& h{habits[index - 1]};

        if(!h.days[cur_wday])
        {
            std::cout << "На сегодня нет этой привычки" << "\n";
            std::cout << "Нажмите Enter для возращения в меню: ";
            std::cin.ignore();
            std::cin.get();
            return;
        }
        
        if (h.is_boolean) 
        {
            std::cout << "Выполнено? (1 - да, 0 - нет): ";
            std::cin >> h.completed[cur_wday];   
        }
        else 
        {
            std::cout << "Введите текущее значение: ";
            std::cin >> h.current_value[cur_wday];
            
            if (h.current_value[cur_wday] >= h.target_value)
            {
                h.completed[cur_wday] = 1;
                std::cout << "Цель достигнута!\n";
            }
        }
        
        saveToFile();
        std::cout << "Прогресс обновлен!\n";
    }
}