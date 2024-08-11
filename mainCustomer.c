#include "customer.h"
#include "common.h"

int main()
{
    int selection;
    char table_id[MAX_PATH];
    int food_id;
    int quantity;
    printf("Which table do you choose sir/madam? ");
    scanf("%s",&table_id);
    do
    {   
        display_menu();
        printf("Place Order (1)\nUpdate Quantity (2)\nCancel Order (3)\nPay the Bill (4)\nShow Orders (5)\nClose Customer Panel (0)\n");
        scanf("%d",&selection);

        switch (selection)
        {
            case 1:
            printf("Which food would you choosing sir/madam? ");
            scanf("%d", &food_id);
            printf("Excellent choice! how many would you want of this food? ");
            scanf("%d", &quantity);
            printf("Excellent! your order will be ready in time.\n");
            place_order(table_id,food_id,quantity);
            break;

            case 2:
            printf("Which food would you like to update quantity of sir/madam? ");
            scanf("%d", &food_id);
            printf("How many would you want of this food? ");
            scanf("%d", &quantity);
            printf("Excellent! I will update your oder shortly. ");
            update_quantity(table_id,food_id,quantity);
            break;

            case 3:
            printf("Which food Would you like to cancel? ");
            scanf("%d",&food_id);
            printf("OK I will cancel your order");
            cancel_order(table_id,food_id);
            break;

            case 4:
            pay_the_bill(table_id);
            break;

            case 5:
            show_orders(table_id);
            break;
        }
    }
    while (selection != 0);
}