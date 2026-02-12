#include <iostream>
#include <cstdio>
#include <cstring>

#define MAX_HABITS 100
#define NAME_LEN 100

struct Habit {
    char name[NAME_LEN];
    int daysFrequency;     
    int isBoolean;         
    int targetValue;
    int currentValue;
    int completed;        
    int days[7];           
};

Habit habits[MAX_HABITS];
int habitCount = 0;
const char* fileName = "habits_data.txt";

void loadFromFile() {
    FILE* file = std::fopen(fileName, "r");
    if (!file) return;
    
    std::fscanf(file, "%d\n", &habitCount);
    for (int i = 0; i < habitCount; ++i) {
        std::fgets(habits[i].name, NAME_LEN, file);
        char* newline = std::strchr(habits[i].name, '\n');
        if (newline) *newline = '\0';
        
        std::fscanf(file, "%d\n", &habits[i].daysFrequency);
        std::fscanf(file, "%d\n", &habits[i].isBoolean);
        std::fscanf(file, "%d\n", &habits[i].targetValue);
        std::fscanf(file, "%d\n", &habits[i].currentValue);
        std::fscanf(file, "%d\n", &habits[i].completed);
        
        for (int j = 0; j < 7; ++j) {
            std::fscanf(file, "%d\n", &habits[i].days[j]);
        }
    }
    std::fclose(file);
}

void saveToFile() {
    FILE* file = std::fopen(fileName, "w");
    if (!file) return;
    
    std::fprintf(file, "%d\n", habitCount);
    for (int i = 0; i < habitCount; ++i) {
        std::fprintf(file, "%s\n", habits[i].name);
        std::fprintf(file, "%d\n", habits[i].daysFrequency);
        std::fprintf(file, "%d\n", habits[i].isBoolean);
        std::fprintf(file, "%d\n", habits[i].targetValue);
        std::fprintf(file, "%d\n", habits[i].currentValue);
        std::fprintf(file, "%d\n", habits[i].completed);
        for (int j = 0; j < 7; ++j) {
            std::fprintf(file, "%d\n", habits[i].days[j]);
        }
    }
    std::fclose(file);
}

void addHabit() {
    if (habitCount >= MAX_HABITS) {
        std::cout << "Достигнут максимум привычек\n";
        return;
    }
    
    Habit h;
    h.name[0] = '\0';
    h.daysFrequency = 0;
    h.isBoolean = 1;
    h.targetValue = 0;
    h.currentValue = 0;
    h.completed = 0;
    for (int i = 0; i < 7; ++i) h.days[i] = 0;
    
    std::cout << "Введите название привычки: ";
    std::cin.ignore();
    std::cin.getline(h.name, NAME_LEN);
    
    std::cout << "Введите частоту повторения (в днях): ";
    std::cin >> h.daysFrequency;
    
    std::cout << "Тип привычки (0 - да/нет, 1 - число): ";
    int type;
    std::cin >> type;
    h.isBoolean = (type == 0) ? 1 : 0;
    
    if (!h.isBoolean) {
        std::cout << "Введите целевое значение: ";
        std::cin >> h.targetValue;
    }
    
    std::cout << "Выберите дни недели (введите номера дней через пробел, 0 для выхода):\n";
    std::cout << "1 - Пн 2 - Вт 3 - Ср 4 - Чт 5 - Пт 6 - Сб 7 - Вс\n";
    
    int dayNum;
    while (std::cin >> dayNum && dayNum != 0) {
        if (dayNum >= 1 && dayNum <= 7) {
            h.days[dayNum-1] = 1;
        }
    }
    std::cin.ignore();
    
    habits[habitCount] = h;
    ++habitCount;
    std::cout << "Привычка добавлена!\n";
    saveToFile();
}

void removeHabit() {
    if (habitCount == 0) {
        std::cout << "Список привычек пуст\n";
        return;
    }
    
    for (int i = 0; i < habitCount; ++i) {
        std::cout << i + 1 << ". " << habits[i].name << "\n";
    }
    
    std::cout << "Введите номер привычки для удаления: ";
    int index;
    std::cin >> index;
    std::cin.ignore();
    
    if (index > 0 && index <= habitCount) {
        for (int i = index - 1; i < habitCount - 1; ++i) {
            habits[i] = habits[i + 1];
        }
        --habitCount;
        std::cout << "Привычка удалена!\n";
        saveToFile();
    }
}

void showWeeklySchedule() {
    const char* dayNames[7] = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    
    std::cout << "============ РАСПИСАНИЕ НА НЕДЕЛЮ ============\n\n";
    
    for (int i = 0; i < 7; ++i) {
        std::cout << dayNames[i] << ":\n";
        int hasHabits = 0;
        
        for (int j = 0; j < habitCount; ++j) {
            if (habits[j].days[i] == 1) {
                std::cout << "  - " << habits[j].name;
                std::cout << " (каждые " << habits[j].daysFrequency << " дн.)";
                
                if (habits[j].isBoolean) {
                    std::cout << " [да/нет]";
                    if (habits[j].completed) std::cout << " (выполнено)";
                } else {
                    std::cout << " [" << habits[j].currentValue << "/" << habits[j].targetValue << "]";
                }
                std::cout << "\n";
                hasHabits = 1;
            }
        }
        
        if (!hasHabits) {
            std::cout << "  Нет привычек\n";
        }
        std::cout << "\n";
    }
}

void updateProgress() {
    if (habitCount == 0) {
        std::cout << "Список привычек пуст\n";
        return;
    }
    
    for (int i = 0; i < habitCount; ++i) {
        std::cout << i + 1 << ". " << habits[i].name << "\n";
    }
    
    std::cout << "Выберите привычку: ";
    int index;
    std::cin >> index;
    std::cin.ignore();
    
    if (index > 0 && index <= habitCount) {
        Habit* h = &habits[index - 1];
        
        if (h->isBoolean) {
            std::cout << "Выполнено? (1 - да, 0 - нет): ";
            std::cin >> h->completed;
            std::cin.ignore();
        } else {
            std::cout << "Введите текущее значение: ";
            std::cin >> h->currentValue;
            std::cin.ignore();
            
            if (h->currentValue >= h->targetValue) {
                h->completed = 1;
                std::cout << "Цель достигнута!\n";
            }
        }
        
        saveToFile();
        std::cout << "Прогресс обновлен!\n";
    }
}

int main() {
    loadFromFile();
    
    int choice;
    do {
        std::cout << "\n===== ТРЕКЕР ПРИВЫЧЕК =====\n";
        std::cout << "1. Добавить привычку\n";
        std::cout << "2. Удалить привычку\n";
        std::cout << "3. Показать расписание\n";
        std::cout << "4. Обновить прогресс\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                addHabit();
                break;
            case 2:
                removeHabit();
                break;
            case 3:
                showWeeklySchedule();
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