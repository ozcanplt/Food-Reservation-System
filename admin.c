#include "admin.h"
#include "common.h"

char *ordersFileName = "Orders.txt";

int add_table(const char *tableId)
{
    DIR *dir;
    if ((dir = opendir(tableId)) == NULL)
    {
        printf("Table no %s is created successfully....\n", tableId);
       _mkdir(tableId);
       char filePath[256];
       snprintf(filePath, sizeof(filePath), "%s//%s", tableId, ordersFileName);
       FILE *file = fopen(filePath, "ab+");
       fclose(file);

       writeToLogFile("Table created succesfully",tableId);
    }
    else
    {
        closedir(dir);
        printf("This table already exists!!!\n");

        writeToLogFile("Table already exists",tableId);
    }
}

void remove_table(const char *tableId) 
{
    if( ( opendir(tableId)) != NULL)
    {
        char temp[50];
        strcpy(temp,tableId);
        strcat(temp,"//");
        strcat(temp,ordersFileName);
        remove(temp);
        rmdir(tableId);
        printf("%s is deleted successfully....\n",tableId);
		
		writeToLogFile("Table removed",tableId);
    }
    else
    {
        printf("There is no Table with the given ID!!!\n");

        writeToLogFile("Table not found",tableId);
    }
}

void check_order()
{
    FILE *ptr;
    TakenOrder order;
    int appr;
    char path[MAX_PATH];

    ptr = fopen("takenOrders.txt", "rb+");
    if (ptr == NULL) 
    {
        printf("Error opening takenOrders.txt file.\n");
        writeToLogFile("Error at opening","TakenOrders.txt");
        return;
    }

    fseek (ptr, 0, SEEK_END);
    long size = ftell(ptr);
    if (size == 0)
    {
        printf("No current orders!\n");
        writeToLogFile("No current orders at","ClosedOrders.txt");
        fclose(ptr);
        return;
    }
    rewind(ptr);

    long pos = 0;

    while (fread(&order, sizeof(TakenOrder), 1, ptr) == 1) 
    {
        pos = ftell(ptr);

        printf("Table: %s\n", order.tableId);
        printf("Food: %s\n", order.f.name);
        printf("Quantity: %d\n", order.quantity);
        printf("Status: %s\n", order.isActive ? "Active" : "Not active");
        printf("Do you approve this order? (1 for approve, 0 for reject): ");
        scanf("%d", &appr);

        order.isConfirmed = (appr == 1);
        order.isActive = (appr == 1);

        fseek(ptr, pos -(long)sizeof(TakenOrder), SEEK_SET);
        fwrite(&order, (long)sizeof(TakenOrder), 1, ptr);
        fseek(ptr, pos, SEEK_SET);

        
        snprintf(path, sizeof(path), "%s/%s", order.tableId, ordersFileName);
        FILE *orders_ptr = fopen(path, "ab");
        if (orders_ptr != NULL)
        {
            fwrite(&order, (long)sizeof(TakenOrder), 1, orders_ptr);
            fclose(orders_ptr);
            writeToLogFile("Order written to the Orders.txt",order.tableId);
        }            
        else
        {
            printf("Error opening Orders.txt for table %s\n", order.tableId);
            writeToLogFile("Error at writing to Orders.txt",order.tableId);
        }
        
    }

    fclose(ptr);

    ptr = fopen("TakenOrders.txt","wb");
    if (ptr != NULL)
    {
        fclose(ptr);
        writeToLogFile("TakenOrders Cleared","");
    }
}

void show_all_invoices()
{
    FILE *ptr;
    float amount;
    int count = 0;
    float total = 0.0;

    ptr = fopen("closedOrders.txt", "r");
    if (ptr == NULL) 
    {
        printf("Error opening closedOrders.txt file.\n");
        writeToLogFile("Error at opening","TakenOrders.txt");
        return;
    }

    printf("Invoices: \n");
    printf("Order #\tAmount\n");
    printf("-------------------\n");
    while (fscanf(ptr, "%f", &amount) == 1)
    {
        count++;
        total += amount;
        printf("%d\t$%.2f\n", count ,amount);
    }

    printf("-------------------\n");
    printf("Total:\t$%.2f\n",total);

    fclose(ptr);
    writeToLogFile("Show Invoices End","");
}

void update_food(int foodId, float new_fee)
{
    FILE *ptr;
    ptr = fopen("foods.txt", "rb+");
    if (ptr == NULL) 
    {
        printf("Error opening foods.txt file.\n");
        writeToLogFile("Error at updating","foods.txt");
        return;
    }

    Food food;
    int found = 0;

    while (fread(&food, sizeof(Food), 1, ptr) == 1)
    {
        if (food.id == foodId)
        {
            food.fee = new_fee;
            found = 1;

            fseek(ptr, -((long)sizeof(food)), SEEK_CUR);

            fwrite(&food, sizeof(Food), 1, ptr);
            break;
        }
    }

    fclose(ptr);
    char buffer[50];
    sprintf(buffer, "Food ID: %d", foodId);

    if (found)
    {
        printf("Food item with ID %d updated. new wee: %.2f\n",
        foodId, new_fee);
        writeToLogFile("Food updated", buffer);
    }
    else
    {
        printf("Food item with ID %d not found.\n",foodId);
        writeToLogFile("Food not found",buffer);
    }
}
