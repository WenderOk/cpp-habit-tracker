cmake_minimum_required(VERSION 3.15)
project(HabitTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к папке src
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Путь к FTXUI (находится в src/FTXUI)
set(FTXUI_DIR ${SRC_DIR}/FTXUI)

# Проверяем существование FTXUI
if(NOT EXISTS ${FTXUI_DIR})
    message(FATAL_ERROR "FTXUI directory not found at ${FTXUI_DIR}")
endif()

# Добавляем FTXUI как подпроект
add_subdirectory(${FTXUI_DIR})

# Собираем все .cpp файлы из src
file(GLOB SOURCES 
    ${SRC_DIR}/*.cpp
)

# Создаем исполняемый файл
add_executable(habit_tracker ${SOURCES})

# Подключаем заголовочные файлы
target_include_directories(habit_tracker PRIVATE 
    ${SRC_DIR}
    ${FTXUI_DIR}/include
)

# Линкуем с библиотеками FTXUI
target_link_libraries(habit_tracker
    ftxui-component
    ftxui-dom
    ftxui-screen
)

# Для Windows добавляем необходимые системные библиотеки
if (WIN32)
    target_link_libraries(habit_tracker
        kernel32
        user32
        gdi32
        winspool
        shell32
        ole32
        oleaut32
        uuid
        comdlg32
        advapi32
    )
endif()