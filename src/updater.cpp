#include "habit.h"
#include <iostream>
using namespace std;

void saveToFile();
void showMessage(string msg, string title);
int getWeekday();

int getWeekday() {
    time_t t = time(nullptr);
    tm* tm = localtime(&t);
    int wday = tm->tm_wday;
    return (wday == 0) ? 6 : wday - 1;
}

void updateProgress() {
    system("cls");
    
    if (habit_count == 0) {
        showMessage("Список привычек пуст!", "Ошибка");
        return;
    }
    
    int today = getWeekday();
    const char* dayNames[] = {"ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ", "ВС"};
    
    cout << "\n=== ОБНОВЛЕНИЕ ПРОГРЕССА ===\n";
    cout << "Сегодня: " << dayNames[today] << "\n\n";
    
    int available = 0;
    for (int i = 0; i < habit_count; i++) {
        if (habits[i].days[today]) {
            cout << i+1 << ". " << habits[i].name;
            if (habits[i].is_boolean) {
                if (habits[i].completed[today]) {
                    cout << " [ВЫПОЛНЕНО]";
                }
            } else {
                cout << " [" << habits[i].current_value[today] 
                     << "/" << habits[i].target_value << "]";
            }
            cout << "\n";
            available++;
        }
    }
    
    if (available == 0) {
        showMessage("На сегодня нет привычек!", "Инфо");
        return;
    }
    
    cout << "\nВыберите (0 - отмена): ";
    int idx;
    cin >> idx;
    
    if (idx == 0) return;
    
    if (idx >= 1 && idx <= habit_count) {
        Habit& h = habits[idx-1];
        
        if (!h.days[today]) {
            showMessage("Нет на сегодня!", "Ошибка");
            return;
        }
        
        if (h.is_boolean) {
            cout << "Выполнено? (1-да, 0-нет): ";
            int val;
            cin >> val;
            
            if (val == 0 || val == 1) {
                h.completed[today] = val;
                saveToFile();
                showMessage(val ? "Отлично!" : "В следующий раз!", val ? "Успех" : "Инфо");
            } else {
                showMessage("Неверно!", "Ошибка");
            }
        } else {
            cout << "Текущее значение: ";
            cin >> h.current_value[today];
            
            if (h.current_value[today] >= h.target_value) {
                h.completed[today] = 1;
                showMessage("Цель достигнута!", "Ура!");
            } else {
                showMessage("Прогресс обновлен!", "Успех");
            }
            saveToFile();
        }
    } else {
        showMessage("Неверный номер!", "Ошибка");
    }
}