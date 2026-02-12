void updateProgress()
{
    std::cout << "\033[2J\033[1;1H";
    if (habit_count == 0)
    {
        std::cout << "Список привычек пуст\n";
        return;
    }
    
    for (int i{}; i < habit_count; i++)
        std::cout << i + 1 << ". " << habits[i].name << "\n";
    
    
    int index{};
    std::cout << "Выберите привычку: ";
    std::cin >> index;
    
    if (index > 0 && index <= habit_count)
    {
        Habit& h = habits[index - 1];
        
        if (h.is_boolean) 
        {
            std::cout << "Выполнено? (1 - да, 0 - нет): ";
            std::cin >> h.completed;   
        }
        else 
        {
            std::cout << "Введите текущее значение: ";
            std::cin >> h.current_value;
            
            if (h.current_value >= h.target_value)
            {
                h.completed = 1;
                std::cout << "Цель достигнута!\n";
            }
        }
        
        saveToFile();
        std::cout << "Прогресс обновлен!\n";
    }
}