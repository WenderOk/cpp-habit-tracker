#include "habit.h"
#include <vector>
#include <string>
#include <iomanip>
#include "FTXUI/include/ftxui/component/screen_interactive.hpp"
#include "FTXUI/include/ftxui/component/component.hpp"

using namespace ftxui;
using namespace std;

int getWeekday();

void showSchedule() {
    auto screen = ScreenInteractive::TerminalOutput();
    
    const char* dayNames[] = {"ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ", "ВС"};
    const char* dayFullNames[] = {"ПОНЕДЕЛЬНИК", "ВТОРНИК", "СРЕДА", 
                                   "ЧЕТВЕРГ", "ПЯТНИЦА", "СУББОТА", "ВОСКРЕСЕНЬЕ"};
    int today = getWeekday();
    
    auto component = Renderer([&] {
        Elements rows;
        
        // Заголовок
        rows.push_back(
            text("========== РАСПИСАНИЕ НА НЕДЕЛЮ ==========") | 
            bold | center | color(Color::Cyan)
        );
        rows.push_back(separator());
        
        // Для каждого дня
        for (int d = 0; d < 7; d++) {
            Elements dayContent;
            
            // Название дня
            string dayTitle = dayFullNames[d];
            if (d == today) {
                dayTitle = ">> " + dayTitle + " <<";
                dayContent.push_back(text(dayTitle) | bold | color(Color::Cyan));
            } else {
                dayContent.push_back(text(dayTitle) | bold);
            }
            
            // Привычки на этот день
            bool hasHabits = false;
            for (int h = 0; h < habit_count; h++) {
                if (habits[h].days[d]) {
                    hasHabits = true;
                    string habitLine = "  • " + string(habits[h].name);
                    
                    if (habits[h].is_boolean) {
                        if (habits[h].completed[d]) {
                            habitLine += " [ВЫПОЛНЕНО]";
                            dayContent.push_back(text(habitLine) | color(Color::Green));
                        } else {
                            habitLine += " [НЕ ВЫПОЛНЕНО]";
                            dayContent.push_back(text(habitLine) | color(Color::Red));
                        }
                    } else {
                        habitLine += " [" + to_string(habits[h].current_value[d]) + 
                                    "/" + to_string(habits[h].target_value) + "]";
                        if (habits[h].completed[d]) {
                            dayContent.push_back(text(habitLine) | color(Color::Green));
                        } else {
                            dayContent.push_back(text(habitLine));
                        }
                    }
                }
            }
            
            if (!hasHabits) {
                dayContent.push_back(text("  • Нет привычек") | dim);
            }
            
            // Добавляем день в виде блока
            rows.push_back(vbox(dayContent) | border);
            rows.push_back(separator());
        }
        
        rows.push_back(text("Нажмите Enter для возврата в меню") | dim | center);
        
        return vbox(rows) | border;
    });
    
    component |= CatchEvent([&](Event event) {
        if (event == Event::Return) {
            screen.Exit();
            return true;
        }
        return false;
    });
    
    screen.Loop(component);
}