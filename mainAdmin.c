#include "admin.h"
#include "common.h"

void create_food_menu() 
{
    FILE *foods_ptr;
    Food food;
    foods_ptr = fopen("foods.txt", "wb");
    
    if (foods_ptr == NULL) 
    {
        writeToLogFile("Error opening foods.txt", "");
        return;
    }

    for(int i = 0; i < 4; i++) 
    {
        sprintf(food.name, "food_%d", i);
        food.fee = i * 5.0f;
        food.id = 1000 + i;
        
        if (fwrite(&food, sizeof(Food), 1, foods_ptr) != 1) 
        {
            writeToLogFile("Error writing to foods.txt", "");
            fclose(foods_ptr);
            return;
        }
    }

    writeToLogFile("Foods have been created", "");
    fclose(foods_ptr);
}

int main()
{   
    int selection;
    char table_id[MAX_PATH];
    int new_fee;
    int food_id;

    do 
    {
        printf("Add a new Table (1)\nRemove an existing table (2)\nCheck Order (3)\nShow Invoices (4)\nUpdate Food (5)\nDisplay Menu (6)\nShow Orders (7)\nClose the Admin Panel (0)\n");
        scanf("%d", &selection);

        switch (selection)
        {
            case 1:
            printf("Enter Table ID: ");
            scanf("%s",&table_id);
            add_table(table_id);
            break;

            case 2:
            printf("Enter Table ID: ");
            scanf("%s",&table_id);
            remove_table(table_id);
            break;

            case 3:
            check_order();
            break;

            case 4:
            show_all_invoices();
            break;

            case 5:
            printf("Enter food Id of the food to be Updated: ");
            scanf("%d",&food_id);
            printf("Enter the new fee of the food with ID %d: ",food_id);
            scanf("%d",&new_fee);
            update_food(food_id, new_fee);
            break;

            case 6:
            display_menu();
            break;

            case 7:
            printf("Table Id for the Orders to be shown: ");
            scanf("%s",&table_id);
            show_orders(table_id);
            break;
        }
        
    }
    while (selection != 0);

    return 0;
}