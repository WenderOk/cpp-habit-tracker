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