#include "error.h"
#include <stdio.h>

void print_error(sqlite3 *db, const char *msg) {
    if (db) {
        fprintf(stderr, "%s: %s\n", msg, sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "%s\n", msg);
    }
}
