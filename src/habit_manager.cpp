void addHabit()
{
    std::cout << "\033[2J\033[1;1H";

    if (habit_count >= MAX_HABITS)
    {
        std::cout << "Достигнут максимум привычек\n";
        return;
    }
    
    Habit h{};
    
    std::cout << "Введите название привычки: ";
    std::cin.ignore(); // Для очистки буфера от \n
    std::cin.getline(h.name, NAME_LEN); // берем строку вместе с проблелом
    
    std::cout << "Тип привычки (1 - да/нет, 0 - число): ";
    std::cin >> h.is_boolean;
    
    if (!h.is_boolean)
    {
        std::cout << "Введите целевое значение: ";
        std::cin >> h.target_value;
    }
    
    std::cout << "Выберите дни недели (введите номера дней через пробел, 0 для выхода):\n";
    std::cout << "1 - Пн 2 - Вт 3 - Ср 4 - Чт 5 - Пт 6 - Сб 7 - Вс\n";
    
    int dayNum{};
    while (std::cin >> dayNum && dayNum != 0)
    {
        if (dayNum >= 1 && dayNum <= 7)
            h.days[dayNum-1] = 1;
    }
    
    habits[habit_count] = h;
    habit_count++;
    std::cout << "Привычка добавлена!\n";
    saveToFile();
}

void removeHabit()
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
    std::cout << "Введите номер привычки для удаления: ";
    std::cin >> index;
    
    if (index > 0 && index <= habit_count)
    {
        for (int i{index - 1}; i < habit_count - 1; i++)
            habits[i] = habits[i + 1];
        
        habit_count--;
        std::cout << "Привычка удалена!\n";
        saveToFile();
    }
}