#include "ui.h"
#include "task_manager.h"
#include "db.h"
#include "error.h"
#include <stdio.h>  // For printf
#include <stdlib.h> // For malloc, free
#include <string.h> // For strtok, strcmp
#include <unistd.h> // For getcwd

#define MAX_PATH_LENGTH 1024

#ifdef __APPLE__
#include <mach-o/dyld.h> // For macOS specific function
#include <libgen.h>     // For dirname (POSIX)
#elif defined(__linux__)
#include <unistd.h>     // For readlink
#include <libgen.h>     // For dirname (POSIX)
#endif

// Function to load the database path from the config file
char* load_db_path(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen() error");
        return NULL;
    }

    char line[MAX_PATH_LENGTH];
    char *path = NULL;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "db_path=", 8) == 0) {
            path = strdup(line + 8); // Skip "db_path=" and copy the rest
            // Remove newline character if present
            path[strcspn(path, "\n")] = '\0';
            break;
        }
    }

    fclose(file);
    return path;
}

// Function to get the directory where the executable is located
const char* get_executable_path() {
    static char path[MAX_PATH_LENGTH];
    
#ifdef __APPLE__
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        return dirname(path);
    }
#elif defined(__linux__)
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len != -1) {
        path[len] = '\0';
        return dirname(path);
    }
#endif

    return NULL;
}

void run_task_manager() {
    sqlite3 *db;
    const char *config_file = "config.properties"; // Relative path
    char config_file_path[MAX_PATH_LENGTH];

    const char *exe_dir = get_executable_path();
    if (exe_dir == NULL) {
        fprintf(stderr, "Failed to get the executable path.\n");
        return;
    }

    snprintf(config_file_path, sizeof(config_file_path), "%s/%s", exe_dir, config_file);

    char *db_file = load_db_path(config_file_path);
    if (db_file == NULL) {
        fprintf(stderr, "Failed to load database path from property file.\n");
        return;
    }

    printf("Database path: %s\n", db_file);

    int rc = db_open(&db, db_file);
    free(db_file);

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
