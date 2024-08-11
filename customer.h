#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdlib.h>
#include <direct.h>
#include <errno.h>
#include <io.h>
#include <dirent.h>
#include <sys/stat.h>

void place_order(char *tableId, int foodId, int quantity);
void update_quantity(char *tableId, int foodId, int new_quantity);
void cancel_order(char *tableId, int foodId);
void pay_the_bill(char *tableId);

#endif