#include <stdio.h>
#include <stdlib.h>
#include <string.h>   // Include for string functions like strcpy()
#include "task_model.h"
#include "db.h"

// Get day name from number
const char* get_day_name(int day_num) {
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    if (day_num >= 0 && day_num < 7) {
        return days[day_num];
    }
    return "Invalid day";
}

void task_add_record(sqlite3 *db) {
    TaskRecord record;
    Task tasks[10];
    int task_count = 0;
    int task_choice;

    // Load all tasks from the database
    task_load_all(db, tasks, &task_count);

    printf("Enter the day of the week (0 for Sunday, 1 for Monday, etc.): ");
    if (scanf("%d", &record.day_num) != 1 || record.day_num < 0 || record.day_num > 6) {
        printf("Invalid day input.\n");
        return;
    }

    strcpy(record.day, get_day_name(record.day_num));
    record.week_number = db_get_week_number();

    if (task_count > 0) {
        printf("Select your task:\n");
        for (int i = 0; i < task_count; i++) {
            printf("%d. %s\n", i + 1, tasks[i].name);
        }

        if (scanf("%d", &task_choice) != 1 || task_choice <= 0 || task_choice > task_count) {
            printf("Invalid task choice.\n");
            return;
        }

        record.task = tasks[task_choice - 1];
        printf("How many hours did you spend on this task? ");
        if (scanf("%f", &record.time_spent) != 1 || record.time_spent < 0) {
            printf("Invalid time input.\n");
            return;
        }

        db_insert_task_record(db, &record);
    } else {
        printf("No tasks found in the database.\n");
    }
}

void task_show_records(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT week_number, day, task, time FROM TaskRecords";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\nWeek | Day       | Task            | Time\n");
    printf("---------------------------------------------\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int week_number = sqlite3_column_int(stmt, 0);
        const unsigned char *day = sqlite3_column_text(stmt, 1);
        const unsigned char *task = sqlite3_column_text(stmt, 2);
        float time_spent = (float)sqlite3_column_double(stmt, 3);

        printf("%d   | %-9s | %-15s | %.2f\n", week_number, day, task, time_spent); 
    }

    sqlite3_finalize(stmt);
}

void task_create_mail_report(sqlite3 *db) {
    printf("I wanted to provide a summary of my progress and achievements for the past week:\n\n");

    printf("Billable Activities:\n\n");

    sqlite3_stmt *stmt;
    const char *sql = "SELECT task, SUM(time) FROM TaskRecords WHERE week_number = ? GROUP BY task";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return;
    }

    int week_number = db_get_week_number();
    sqlite3_bind_int(stmt, 1, week_number);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *task = sqlite3_column_text(stmt, 0);
        float time_spent = (float)sqlite3_column_double(stmt, 1);  // Retrieve REAL as float

        printf("%s: %.2f Hours\n", task, time_spent);  // Display with two decimal places
    }

    sqlite3_finalize(stmt);

}

void task_add_new(sqlite3 *db) {
    char task_name[50];

    printf("Enter the name of the new task: ");
    if (scanf(" %[^\n]%*c", task_name) != 1) {
        printf("Invalid task name input.\n");
        return;
    }

    db_insert_task(db, task_name);
}
