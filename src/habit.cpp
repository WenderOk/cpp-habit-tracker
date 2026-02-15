struct Habit
{
    char name[NAME_LEN];
    bool is_boolean;         
    int target_value;
    int current_value[7];
    int completed[7];        
    int days[7];           
};