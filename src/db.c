#include "db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int db_open(sqlite3 **db, const char *filename) {
    return sqlite3_open(filename, db);
}

void db_close(sqlite3 *db) {
    sqlite3_close(db);
}

void db_initialize(sqlite3 *db) {
    char *err_msg = 0;

    const char *create_task_table_sql = "CREATE TABLE IF NOT EXISTS Tasks ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                        "name TEXT UNIQUE);";

    int rc = sqlite3_exec(db, create_task_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return;
    }

    const char *create_task_records_table_sql = "CREATE TABLE IF NOT EXISTS TaskRecords ("
                                                "week_number INTEGER, "
                                                "day TEXT, "
                                                "task TEXT, "
                                                "time REAL);";

    rc = sqlite3_exec(db, create_task_records_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

// Other database functions...


int db_get_week_number() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buffer[3];
    strftime(buffer, sizeof(buffer), "%V", tm); // Get the week number
    return atoi(buffer);
}

void db_insert_task_record(sqlite3 *db, const TaskRecord *record) {
    char *err_msg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), 
             "INSERT INTO TaskRecords (week_number, day, task, time) VALUES (%d, '%s', '%s', %f);", 
             record->week_number, record->day, record->task.name, record->time_spent);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Task record inserted successfully.\n");
    }
}

void db_insert_task(sqlite3 *db, const char *task_name) {
    char *err_msg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO Tasks (name) VALUES ('%s');", task_name);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Task '%s' added successfully.\n", task_name);
    }
}

void task_load_all(sqlite3 *db, Task tasks[], int *task_count) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, name FROM Tasks ORDER BY name ASC";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch tasks: %s\n", sqlite3_errmsg(db));
        return;
    }

    *task_count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        tasks[*task_count].id = sqlite3_column_int(stmt, 0);
        strcpy(tasks[*task_count].name, (const char *)sqlite3_column_text(stmt, 1));
        (*task_count)++;
    }

    sqlite3_finalize(stmt);
}
