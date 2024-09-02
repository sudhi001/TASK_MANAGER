#ifndef ERROR_H
#define ERROR_H

#include <sqlite3.h>

void print_error(sqlite3 *db, const char *msg);

#endif // ERROR_H
