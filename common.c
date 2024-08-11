#include "common.h"

//char *fileLog = "log.txt";

void display_menu()
{
    FILE *ptr;
    Food food;

    ptr = fopen("Foods.txt", "rb");
    if (ptr == NULL) 
    {
        printf("Error opening Foods.txt file.\n");
        return;
    }

    printf("Food Menu:\n");
    printf("ID\tName\t\tPrice\n");
    while (fread(&food, sizeof(Food), 1, ptr) == 1) 
    {
        printf("%d\t%-15s\t$%.2f\n", 
        food.id, 
        food.name, 
        food.fee);
    }
    fclose(ptr);
}

void show_orders(const char *tableId)
{
    FILE *ptr;
    TakenOrder orders;
    char path[250];
    sprintf(path, "%s/Orders.txt",tableId);

    ptr = fopen(path, "rb");
    if (ptr == NULL) 
    {
        printf("Error opening Orders.txt file.\n");
        return;
    }

    printf("Taken Orders:\n");
    printf("Food Name\tQuantity\tPrice\tConfirmed?\tActive?\n");
    while (fread(&orders, sizeof(TakenOrder), 1, ptr) == 1) 
    {
        printf("%s\t\t%d\t\t%.2f\t%s\t\t%s\n", 
        orders.f.name, 
        orders.quantity, 
        orders.f.fee, 
        orders.isConfirmed ? "Yes" : "No", 
        orders.isActive ? "Yes" : "No");
    }
    fclose(ptr);
}

void writeToLogFile(const char* action, const char* details) 
{
    FILE *file = fopen("log.txt", "a");
    if (file == NULL) 
    {
        printf("Error opening log file\n");
        return;
    }

    char msg[100];

    fprintf(file,"%s",msg);

    time_t now = time(NULL);
    char timestamp[26];
    ctime_s(timestamp, sizeof(timestamp), &now);
    timestamp[24] = '\0';  // Remove newline added by ctime_s

    fprintf(file, "[%s] %s: %s\n", timestamp, action, details);
    fclose(file);
}