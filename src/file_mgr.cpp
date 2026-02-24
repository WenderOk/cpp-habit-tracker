#include <iostream>
#include <cstdio>
#include <cstring>
#include "habit.h"

void saveToFile()
{
    FILE* file = std::fopen(fileName, "w");
    if (!file) return;
    
    std::fprintf(file, "%d\n", habit_count);
    for (int i{}; i < habit_count; i++)
    {
        std::fprintf(file, "%s\n", habits[i].name);
        std::fprintf(file, "%d\n", habits[i].is_boolean);
        
        if(!habits[i].is_boolean)
        {
            std::fprintf(file, "%d\n", habits[i].target_value);
            for (int j{}; j < 7; j++)
                std::fprintf(file, "%d\n", habits[i].current_value[j]);
        }
        else
        {
            std::fprintf(file, "%d\n", habits[i].target_value);
            for (int j{}; j < 7; j++)
                std::fprintf(file, "%d\n", habits[i].completed[j]);
        }

        for (int j{}; j < 7; j++)
            std::fprintf(file, "%d\n", habits[i].days[j]);
    }
    std::fclose(file);
}

void loadFromFile()
{
    FILE* file{std::fopen(fileName, "r")};
    if (!file) return;
    
    std::fscanf(file, "%d\n", &habit_count);
    for (int i{}; i < habit_count; i++)
    {
        std::fgets(habits[i].name, NAME_LEN, file);
        char* newline{std::strchr(habits[i].name, '\n')};
        if (newline) *newline = '\0';
        
        std::fscanf(file, "%d\n", &habits[i].is_boolean);
        std::fscanf(file, "%d\n", &habits[i].target_value);
        
        if(!habits[i].is_boolean)
        {
            for (int j{}; j < 7; j++)
                std::fscanf(file, "%d\n", &habits[i].current_value[j]);
        }
        else
        {
            for (int j{}; j < 7; j++)
                std::fscanf(file, "%d\n", &habits[i].completed[j]);
        }
        
        for (int j{}; j < 7; j++)
            std::fscanf(file, "%d\n", &habits[i].days[j]);
    }
    std::fclose(file);
}