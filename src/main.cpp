#include <iostream>
#include <cstdio>
#include <cstring>

#define MAX_HABITS 50
#define NAME_LEN 50

struct Habit
{
    char name[NAME_LEN];
    int days_frequency;     
    bool is_boolean;         
    int target_value;
    int current_value;
    int completed;        
    int days[7];           
};

Habit habits[MAX_HABITS];
int habit_count{};
const char* fileName = "habits_data.txt";

void loadFromFile()
{
    FILE* file = std::fopen(fileName, "r");
    if (!file) return;
    
    std::fscanf(file, "%d\n", &habit_count);
    for (int i{}; i < habit_count; i++)
    {
        std::fgets(habits[i].name, NAME_LEN, file);
        char* newline = std::strchr(habits[i].name, '\n');
        if (newline) *newline = '\0';
        
        std::fscanf(file, "%d\n", &habits[i].days_frequency);
        std::fscanf(file, "%d\n", &habits[i].is_boolean);
        std::fscanf(file, "%d\n", &habits[i].target_value);
        std::fscanf(file, "%d\n", &habits[i].current_value);
        std::fscanf(file, "%d\n", &habits[i].completed);
        
        for (int j{}; j < 7; j++)
            std::fscanf(file, "%d\n", &habits[i].days[j]);
    }
    std::fclose(file);
}

void saveToFile()
{
    FILE* file = std::fopen(fileName, "w");
    if (!file) return;
    
    std::fprintf(file, "%d\n", habit_count);
    for (int i{}; i < habit_count; i++)
    {
        std::fprintf(file, "%s\n", habits[i].name);
        std::fprintf(file, "%d\n", habits[i].days_frequency);
        std::fprintf(file, "%d\n", habits[i].is_boolean);
        std::fprintf(file, "%d\n", habits[i].target_value);
        std::fprintf(file, "%d\n", habits[i].current_value);
        std::fprintf(file, "%d\n", habits[i].completed);
        for (int j{}; j < 7; j++)
            std::fprintf(file, "%d\n", habits[i].days[j]);
    }
    std::fclose(file);
}

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
    
    std::cout << "Введите частоту повторения (в днях): ";
    std::cin >> h.days_frequency;
    
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
        for (int i = index - 1; i < habit_count - 1; i++)
            habits[i] = habits[i + 1];
        
        habit_count--;
        std::cout << "Привычка удалена!\n";
        saveToFile();
    }
}

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
        }
    } while (choice != 5);
    
    return 0;
}