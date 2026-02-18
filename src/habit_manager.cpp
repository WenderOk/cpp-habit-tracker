void addHabit()
{
    std::cout << "\033[2J\033[1;1H";

    if (habit_count >= MAX_HABITS)
    {
        std::cout << "Достигнут максимум привычек\n";
        wait_input();
        return;
    }

    Habit h{};
    
    std::cout << "Введите название привычки: ";
    std::cin.ignore(); // Для очистки буфера от \n
    std::cin.getline(h.name, NAME_LEN); // берем строку вместе с проблелом
    
    int input{};
    std::cout << "Тип привычки (1 - да/нет, 0 - число): ";
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
            h.is_boolean = (input == 1) ? 1 : 0;
            break;
        } 
    }
    
    if (!h.is_boolean)
    {
        std::cout << "Введите целевое значение: ";
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
                h.target_value = input;
                break;
            } 
        }
    }
    
    std::cout << "Выберите дни недели (введите номера дней через Enter, 0 для выхода):\n";
    std::cout << "1 - Пн 2 - Вт 3 - Ср 4 - Чт 5 - Пт 6 - Сб 7 - Вс\n";
    
    int dayNum{};
    while (true) // Проверка на корректность ввода
    {
        std::cin >> dayNum;
        if (std::cin.fail() || (std::cin.peek() != '\n') || ((dayNum < 0) || (dayNum > 7)))
        {
            std::cout << "Введено некорректное значение!\nвведите номера дней через Enter, 0 для выхода: \n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');                    
        }
        else
        {
            if(dayNum == 0) break;
            h.days[dayNum-1] = 1;   
        }
    } 
    
    habits[habit_count] = h;
    habit_count++;
    std::cout << "Привычка добавлена!\n";
    saveToFile();
    wait_input();
}

void removeHabit()
{
    std::cout << "\033[2J\033[1;1H";

    if (habit_count == 0)
    {
        std::cout << "Список привычек пуст\n";
        wait_input();
        return;
    }
    
    for (int i{}; i < habit_count; i++)
        std::cout << i + 1 << ". " << habits[i].name << "\n";
    
    int index{};
    std::cout << "Введите номер привычки для удаления: ";
    
    while(true) // Проверка на корректность ввода
    {
        std::cin >> index;
        if (std::cin.fail() || (std::cin.peek() != '\n') || ((index < 0) || (index > habit_count)))
        {
            std::cout << "Введено некорректное значение!\nВведите номер привычки из списка: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else
        {
            for (int i{index - 1}; i < habit_count - 1; i++)
                habits[i] = habits[i + 1];
            
            habit_count--;
            std::cout << "Привычка удалена!\n";
            saveToFile();
            wait_input();
            break;
        }
    }
    
}