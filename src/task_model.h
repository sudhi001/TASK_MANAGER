#ifndef TASK_MODEL_H
#define TASK_MODEL_H
#include <sqlite3.h> 

// Define the Task structure
typedef struct {
    int id;
    char name[50];
} Task;

// Define the TaskRecord structure
typedef struct {
    int week_number;
    int day_num;
    char day[10];
    Task task;
    float time_spent;
} TaskRecord;

// Function declarations
void task_add_record(sqlite3 *db);
void task_show_records(sqlite3 *db);
void task_create_mail_report(sqlite3 *db);
void task_add_new(sqlite3 *db);
const char* get_day_name(int day_num);

#endif // TASK_MODEL_H
