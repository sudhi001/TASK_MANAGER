#ifndef DB_H
#define DB_H

#include <sqlite3.h>
#include "task_model.h"

int db_open(sqlite3 **db, const char *filename);
void db_close(sqlite3 *db);
void db_initialize(sqlite3 *db);
int db_get_week_number();
void db_insert_task_record(sqlite3 *db, const TaskRecord *record);
void db_insert_task(sqlite3 *db, const char *task_name);
void task_load_all(sqlite3 *db, Task tasks[], int *task_count);


#endif // DB_H
