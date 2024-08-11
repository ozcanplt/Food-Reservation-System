#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define MAX_PATH 300

// Common data structs for the program

typedef struct
{
    int id;
    char name[50];
    float fee;
} Food;

typedef struct
{
    Food f;
    int quantity;
    char tableId[250];
    bool isConfirmed;
    bool isActive;
} TakenOrder;

// Function Declarations
void display_menu();
void show_orders(const char *tableId);
void writeToLogFile(const char* action, const char* details);

#endif