#include "customer.h"
#include "common.h"
#include <string.h>

void place_order(char *tableId, int foodId, int quantity)
{
    DIR *dir = opendir(tableId);
    if( ( opendir(tableId)) == NULL)
    {
        printf("No table with table ID %s\n",tableId);
        return;
    }
    closedir(dir);

    FILE *food_ptr;
    food_ptr = fopen("Foods.txt", "rb");
    if (food_ptr == NULL)
    {
        printf("Error opening Foods.txt file.\n");
        return;
    }

    Food food;
    bool food_found = false;
    while (fread(&food, sizeof(Food), 1, food_ptr) == 1)
    {
        if (foodId == food.id)
        {
            food_found = true;
            break;
        }
    }
    fclose(food_ptr);

    if (!food_found)
    {
        printf("No food with ID %d\n",foodId);
        return;
    }

    FILE *taken_order_ptr;
    taken_order_ptr = fopen("takenOrders.txt","r+b");
    if (taken_order_ptr == NULL)
    {
        printf("Error oponing takenOrders.txt\n");
        return;
    }

    fseek(taken_order_ptr, 0, SEEK_END);
    long size =  ftell(taken_order_ptr);

    if (size != 0)
    {
        printf("There are inactive order in takenOrders.txt, please resolve the current order first!\n");
        fclose(taken_order_ptr);
        return;
    }

    TakenOrder order;
    order.f = food;
    order.isActive = true;
    order.isConfirmed = false;
    order.quantity = quantity;
    strcpy(order.tableId, tableId);

    fwrite(&order, sizeof(TakenOrder), 1, taken_order_ptr);

    fclose(taken_order_ptr);
}

void update_quantity(char *tableId, int foodId, int new_quantity)
{
    char path[MAX_PATH];
    sprintf(path, "%s\\Orders.txt", tableId);
    FILE *order_ptr;
    order_ptr = fopen(path,"r+b");
    if (order_ptr == NULL)
    {
        printf("Error oponing Orders.txt\n");
        return;
    }
    TakenOrder order;
    int found = 0;

    while (fread(&order, sizeof(TakenOrder), 1, order_ptr) == 1)
    {
        if (strcmp(order.tableId, tableId) == 0 && order.f.id == foodId && order.isActive)
        {
            order.quantity = new_quantity;
            fseek(order_ptr, -(long)sizeof(TakenOrder), SEEK_CUR);
            fwrite(&order, sizeof(TakenOrder), 1, order_ptr);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Order not found or is not active.\n");
    }

    fclose(order_ptr);
}

void cancel_order(char *tableId, int foodId)
{
    char path[MAX_PATH];
    sprintf(path, "%s\\Orders.txt", tableId);
    FILE *order_ptr;
    order_ptr = fopen(path,"r+b");
    if (order_ptr == NULL)
    {
        printf("Error oponing Orders.txt\n");
        return;
    }
    TakenOrder order;
    int found = 0;

    while (fread(&order, sizeof(TakenOrder), 1, order_ptr) == 1)
    {
        if (strcmp(order.tableId, tableId) == 0 && order.f.id == foodId && order.isActive)
        {
            order.isActive = false;
            fseek(order_ptr, -(long)sizeof(TakenOrder), SEEK_CUR);
            fwrite(&order, (long)sizeof(TakenOrder), 1, order_ptr);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Order not found or is not active.\n");
    }

    fclose(order_ptr);
}

void pay_the_bill(char *tableId)
{
    char path[MAX_PATH];
    sprintf(path, "%s\\Orders.txt", tableId);
    FILE *order_ptr;
    order_ptr = fopen(path,"r+b");
    if (order_ptr == NULL)
    {
        printf("Error oponing Orders.txt\n");
        return;
    }

    TakenOrder order;
    float total_bill = 0.0;

    while (fread(&order, sizeof(TakenOrder), 1, order_ptr) == 1)
    {
        if (strcmp(order.tableId, tableId) == 0 && order.isActive)
        {
            total_bill += order.f.fee * order.quantity;
        }
    }
    fclose(order_ptr);
    order_ptr = fopen(path, "wb");
    if (order_ptr == NULL)
    {
        printf("Error clearing Orders.txt for table %s\n", tableId);
        return;
    }
    fclose(order_ptr);

    FILE *closed_order_ptr;
    closed_order_ptr = fopen("ClosedOrders.txt","r+");
    if (closed_order_ptr == NULL)
    {
        printf("Error oponing ClosedOrders.txt\n");
        return;
    }

    fprintf(closed_order_ptr, "%.2f\n", total_bill);
    fclose(closed_order_ptr);

    printf("Bill paid for table %s: $%.2f\n", tableId, total_bill);

    char buffer[25];
    sprintf(buffer,"$%.2f",total_bill);

    writeToLogFile("Bill Paid",buffer);
}
