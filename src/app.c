#include "ui.h"
#include "task_manager.h"
#include "db.h"
#include "error.h"

void run_task_manager() {
    sqlite3 *db;
    int rc = db_open(&db, "tasks.db");

    if (rc != SQLITE_OK) {
        print_error(db, "Can't open database");
        return;
    }

    db_initialize(db);

    MenuChoice choice;
    do {
        choice = get_user_choice();
        handle_choice(choice, db);
    } while (choice != EXIT);

    db_close(db);
}
