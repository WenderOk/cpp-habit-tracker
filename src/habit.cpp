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