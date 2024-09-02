#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <sqlite3.h>
#include "ui.h"

void handle_choice(MenuChoice choice, sqlite3 *db);

#endif // TASK_MANAGER_H
