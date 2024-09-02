#include <stdio.h>
#include "ui.h"

void print_menu() {
    printf("\nWhat would you like to do?\n");
    printf("1. Enter a task record\n");
    printf("2. Show all task records\n");
    printf("3. Create a mail report\n");
    printf("4. Add a new task\n");
    printf("5. Exit\n");
    printf("Enter your choice (1-5): ");
}

MenuChoice get_user_choice() {
    print_menu();
    int choice;
    scanf("%d", &choice);
    return (MenuChoice)choice;
}
