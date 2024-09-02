#include "ui.h"
#include "task_manager.h"
#include "db.h"
#include "error.h"
#include <stdio.h>  // For printf
#include <stdlib.h> // For getenv
#include <unistd.h> // For getcwd
#include <string.h> // For strcat

void run_task_manager() {
    sqlite3 *db;
    const char *db_file = "tasks.db";
    char full_path[1024]; // Buffer to hold the full path
    char *cwd = getcwd(NULL, 0); // Get current working directory

    if (cwd == NULL) {
        perror("getcwd() error");
        return;
    }

    // Construct the full path
    snprintf(full_path, sizeof(full_path), "%s/%s", cwd, db_file);

    // Print the full path
    printf("Database full path: %s\n", full_path);

    int rc = db_open(&db, full_path);

    if (rc != SQLITE_OK) {
        print_error(db, "Can't open database");
        free(cwd); // Free the memory allocated by getcwd
        return;
    }

    db_initialize(db);

    MenuChoice choice;
    do {
        choice = get_user_choice();
        handle_choice(choice, db);
    } while (choice != EXIT);

    db_close(db);
    free(cwd); // Free the memory allocated by getcwd
}
