#include "habit.h"
#include <iostream>
#include <cstring>
using namespace std;

void saveToFile();
void showMessage(string msg, string title);

void addHabit() {
    system("cls");
    
    if (habit_count >= MAX_HABITS) {
        cout << "\nОШИБКА: Достигнут максимум привычек!\n";
        cout << "\nНажмите Enter...";
        cin.get();
        return;
    }
    
    Habit h;
    
    cout << "\n=== ДОБАВЛЕНИЕ ПРИВЫЧКИ ===\n\n";
    cout << "Название: ";
    cin.ignore();
    cin.getline(h.name, NAME_LEN);
    
    if (strlen(h.name) == 0) {
        showMessage("Имя не может быть пустым!", "Ошибка");
        return;
    }
    
    cout << "\nТип привычки:\n";
    cout << "0 - Числовая\n";
    cout << "1 - Да/Нет\n";
    cout << "Выбор: ";
    cin >> h.is_boolean;
    
    if (!h.is_boolean) {
        cout << "Целевое значение: ";
        cin >> h.target_value;
        
        if (h.target_value <= 0) {
            showMessage("Цель должна быть больше 0!", "Ошибка");
            return;
        }
    }
    
    // Обнуляем массивы
    for (int i = 0; i < 7; i++) {
        h.current_value[i] = 0;
        h.completed[i] = 0;
        h.days[i] = 0;
    }
    
    cout << "\n=== ВЫБОР ДНЕЙ ===\n";
    cout << "1-Пн 2-Вт 3-Ср 4-Чт 5-Пт 6-Сб 7-Вс\n";
    cout << "Вводите числа, 0 - конец\n\n";
    
    int day;
    bool hasDays = false;
    
    while (true) {
        cout << "День: ";
        cin >> day;
        
        if (day == 0) break;
        
        if (day >= 1 && day <= 7) {
            h.days[day-1] = 1;
            hasDays = true;
        }
    }
    
    if (!hasDays) {
        showMessage("Выберите хотя бы один день!", "Ошибка");
        return;
    }
    
    habits[habit_count] = h;
    habit_count++;
    saveToFile();
    
    showMessage("Привычка добавлена!", "Успех");
}

void removeHabit() {
    system("cls");
    
    if (habit_count == 0) {
        showMessage("Список привычек пуст!", "Ошибка");
        return;
    }
    
    cout << "\n=== УДАЛЕНИЕ ПРИВЫЧКИ ===\n\n";
    
    for (int i = 0; i < habit_count; i++) {
        cout << i+1 << ". " << habits[i].name;
        if (habits[i].is_boolean) {
            cout << " [Да/Нет]";
        } else {
            cout << " [Цель: " << habits[i].target_value << "]";
        }
        cout << "\n";
    }
    
    cout << "\nНомер (0 - отмена): ";
    int idx;
    cin >> idx;
    
    if (idx == 0) return;
    
    if (idx >= 1 && idx <= habit_count) {
        cout << "Удалить? (1-да, 0-нет): ";
        int confirm;
        cin >> confirm;
        
        if (confirm) {
            for (int i = idx-1; i < habit_count-1; i++) {
                habits[i] = habits[i+1];
            }
            habit_count--;
            saveToFile();
            showMessage("Привычка удалена!", "Успех");
        }
    } else {
        showMessage("Неверный номер!", "Ошибка");
    }
}