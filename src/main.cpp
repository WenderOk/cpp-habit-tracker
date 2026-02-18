#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>
#include <string>

// Подключаем FTXUI
#include "FTXUI/include/ftxui/component/screen_interactive.hpp"
#include "FTXUI/include/ftxui/component/component.hpp"
#include "FTXUI/include/ftxui/dom/elements.hpp"

#include "habit.h"

using namespace ftxui;
using namespace std;

Habit habits[MAX_HABITS];
int habit_count = 0;
const char* fileName = "habits_data.txt";

// Объявляем функции
void loadFromFile();
void saveToFile();
void addHabit();
void removeHabit();
void showSchedule();
void updateProgress();
int getWeekday();
void showMessage(string msg, string title);

// Подключаем остальные файлы
#include "loader.cpp"
#include "saver.cpp"
#include "habit_manager.cpp"
#include "updater.cpp"
#include "shedule_printer.cpp"

// Простая функция для показа сообщений
void showMessage(string msg, string title) {
    auto screen = ScreenInteractive::TerminalOutput();
    
    // Простой диалог
    auto component = Renderer([&] {
        return vbox({
            text(title) | bold | center,
            separator(),
            text(msg) | center,
            separator(),
            text("Нажмите Enter") | dim,
        }) | center | border;
    });
    
    // Обработка нажатия Enter
    component |= CatchEvent([&](Event event) {
        if (event == Event::Return) {
            screen.Exit();
            return true;
        }
        return false;
    });
    
    screen.Loop(component);
}

// Главное меню
int main() {
    loadFromFile();
    
    auto screen = ScreenInteractive::TerminalOutput();
    
    // Простое меню
    vector<string> menuItems = {
        "1. Добавить привычку",
        "2. Удалить привычку",
        "3. Показать расписание",
        "4. Обновить прогресс",
        "5. Выход"
    };
    
    int selected = 0;
    auto menu = Menu(&menuItems, &selected);
    
    // Создаем интерфейс
    auto component = Renderer(menu, [&] {
        int today = getWeekday();
        int todayCount = 0;
        for (int i = 0; i < habit_count; i++) {
            if (habits[i].days[today]) todayCount++;
        }
        
        return vbox({
            // Заголовок
            text("ТРЕКЕР ПРИВЫЧЕК") | bold | center | color(Color::Cyan),
            separator(),
            
            // Статистика и меню в одной строке
            hbox({
                // Статистика слева
                vbox({
                    text("Статистика") | bold,
                    text("Всего: " + to_string(habit_count)),
                    text("На сегодня: " + to_string(todayCount)),
                }) | border,
                
                // Меню справа
                menu->Render() | border,
            }),
            
            separator(),
            text("Enter - выбрать | Esc - выход") | dim,
        }) | border;
    });
    
    // Обработка выбора пункта меню
    component |= CatchEvent([&](Event event) {
        if (event == Event::Return) {
            screen.Exit(); // Выходим из меню
            
            // Вызываем нужную функцию
            switch(selected) {
                case 0: addHabit(); break;
                case 1: removeHabit(); break;
                case 2: showSchedule(); break;
                case 3: updateProgress(); break;
                case 4: return true; // Выход
            }
            
            // Возвращаемся в меню
            main(); // Простой перезапуск
            return true;
        }
        return false;
    });
    
    screen.Loop(component);
    return 0;
}