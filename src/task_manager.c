#include <stdio.h>       // Include for printf
#include <stddef.h>      // Include for NULL
#include "task_manager.h"
#include "task_model.h"
#include "error.h"

void handle_choice(MenuChoice choice, sqlite3 *db) {
    switch (choice) {
        case ENTER_TASK_RECORD:
            task_add_record(db);
            break;
        case SHOW_TASK_RECORDS:
            task_show_records(db);
            break;
        case CREATE_MAIL_REPORT:
            task_create_mail_report(db);
            break;
        case ADD_NEW_TASK:
            task_add_new(db);
            break;
        case EXIT:
            printf("Exiting...\n");
            break;
        default:
            print_error(NULL, "Invalid choice. Please enter a number between 1 and 5.");
            break;
    }
}
