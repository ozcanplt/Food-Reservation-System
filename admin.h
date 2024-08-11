#ifndef ADMIN_H
#define ADMIN_H

#include <stdlib.h>
#include <direct.h>
#include <errno.h>
#include <io.h>
#include <dirent.h>
#include <sys/stat.h>

int add_table(const char *tableId);
void remove_table(const char *tableId);
void check_order();
void show_all_invoices();
void update_food(int foodId, float new_fee);

#endif