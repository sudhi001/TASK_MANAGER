#ifndef UI_H
#define UI_H

typedef enum {
    ENTER_TASK_RECORD = 1,
    SHOW_TASK_RECORDS,
    CREATE_MAIL_REPORT,
    ADD_NEW_TASK,
    EXIT
} MenuChoice;

MenuChoice get_user_choice();
void print_menu();

#endif // UI_H
