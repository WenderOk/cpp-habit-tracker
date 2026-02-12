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