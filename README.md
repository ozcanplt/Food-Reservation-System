SEN224 – System Programming Lab  

`                          `Spring 2024 – Programming Assignment II                                    Due: Tuesday, 23/04/2024, 23:59   

Requirements:  

1. Only properly demonstrated assignments will be graded.  
1. Assignments should be solved individually, cheating will be penalized. Do not share your answers with other students.
1. Submit the assignment by the deadline, electronically through Google Classroom. 
1. Late submissions will not be accepted.  
1. Just submit your .c and .h files. 
1. Archive your files into a .zip file. Use your student number to build your filename.  Example: “21\*\*\*\*\*\*\*.zip” 

FOOD RESERVATION PROGRAM 

A new restaurant is opening in ATU. The restaurant owner wants to view and manage customers' orders digitally. Therefore, we ask for your help in implementing this software. 

Software Requirements

The basic operation that the restaurant expects from the software is as follows: 

- Customers coming to the restaurant should be seated at a table. Here, each table has an ID. 
- The restaurant owner should be able to add new tables or remove existing one in the restaurant. 
- The food menu should be presented to the customer so that customer can order. The menu must include the ID, name and fee of each food. 
- The restaurant owner should be able to update the fee for an existing food later. 
- When ordering, the customer must provide table ID, food ID and how many of this food customer wants. 
- The order must be submitted to the business's request and, if the order is approved by the business, it must be added to the table's order list. 
- Orders must be taken from only one table at a time and must be submitted for approval. 
- The customer should be able to cancel the order later if customer wishes. 
- The customer should be able to change the quantity of the order if customer wishes. 
- Both the customer and the restaurant owner should be able to instantly view the order list for a table. 
- At the end of the food the customer must pay the total amount. For this, customer  is asked for the table ID. Only foods that have not been canceled must be paid for at checkout. 
- After payment is made, the order list for the table must be deleted and the table must be made ready for new customers. 
- The restaurant owner should be able to check the total payment amounts on the screen at the end of the day. 

Software Design 

The restaurant owner requires two separate software programs from you to perform the specified tasks: admin and customer panels. The functionalities required on both panels are given in table 1. 



|Admin Panel |Customer Panel |Common functions that both panels should have |
| - | - | :-: |
|<p>1. A new table can be added </p><p>2. The  existing  table  can  be removable </p><p>3. It  should  be  checked  whether there is a new order and if so, it should be approved/rejected. </p><p>4. All  payment amounts should be viewable </p><p>5. The  fee  of  a  food  should  be updated </p>|<p>1. Should  be  able  to  place  new orders </p><p>2. Order quantity should be updated </p><p>3. The order can be canceled </p><p>4. Should be able to pay </p>|<p>1. Food menu should be viewable </p><p>2. Should be able to view the order list for a table </p>|

Table 1 Panel functionalities 

1. A folder should be created for each table. The folder name must be the same as the table ID. The type of table ID is char array and its length is 250.  The created folder should be able to be written/read/executed only by the user who created it and the users in the same group. 
1. Orders for a table must be kept in the Orders.txt file within the folder. This file must also be created when creating the table.  
1. The foods on the menu are included in the Foods.txt file. This file contains a fixed number of foods (4) and new ones cannot be added. 
1. Food information stored in the Foods.txt file is in a struct form. The UML diagram of Food Struct is as follows: 



|Food |
| - |
|<p>id: int </p><p>name: char[50] fee: float </p>|

5. Orders placed by the customer must first be written in the TakenOrders.txt file in a struct form. The UML diagram of Struct is as follows: 



|takenOrder |
| - |
|<p>f: Food </p><p>quantity: int tableId: char[250] isConfirmed: bool isActive: bool </p>|

Attribute meanings are as follows: 

- f: ordered food 
- quantity: the number of foods ordered 
- tableId: ID of the table that placed the order 
- isConfirmed: shows whether the order is confirmed or not. It takes the  false value when the first order is placed. It is set to true after the order is confirmed by admin. 
- isActive: Indicates whether the order is active or passive. It gets the true value when the customer places the first order. If the customer cancels the order, it returns false. 
6. Once the order is confirmed, the order in TakenOrders.txt should be written to the Orders.txt file of the relevant table. 
7. After the customer pays, only the total amount should be written to the ClosedOrders.txt (ex: 250.99) file. 
7. In order to follow up the operations within the restaurant, all steps taken should be written to the log.txt file. You can check the logged information for each step by running the .exe files shared with you for sample log file output.

Software Implementation Details 

1. Admin Panel 

Create table: The new table ID is received from the user. If there is no table with the entered ID, a folder and an Orders.txt file for this table must be created. 

Delete table: The table ID is obtained from the user. If there is a table with the entered ID, the folder and Orders.txt file belonging to this table must be deleted. 

Check new order: It should be checked whether there is a new order in takeOrders.txt.  

- If there is, it must be submitted to the admin whether the order is approved or not.  
- If the admin approves, this order should be added to the Orders.txt file of the table that placed the order.  
- Afterwards, the content of the takenOrders.txt file should be reset. 

Show all invoices: All payment information in ClosedOrders.txt should be printed on the screen. 

Update food: Food ID and new fee should be entered by the user. If there is a food with the entered ID, the fee of the food  must be changed in Foods.txt. 

2. Customer Panel 

Place a new order: Table ID of the table placing the order, food ID of the food to be ordered, and order quantity information must be obtained from the customer. 

- If there is a table with the entered table ID and a food with the entered food ID, a new takenOrder (see the takenOrder struct) must be created. 
- However, in order for an order to be received, an order that has been previously taken and has not yet been confirmed must not be in the takenOrders.txt file. If this file is empty, a new order must be processed and written to the takenOrders.txt file. 
- A table may order the same dish more than once. 

Update quantity: The table ID of the table that will update the order, the food ID of the food to be updated, and the new order quantity information must be obtained from the customer.  

- If there is a table with the entered table ID and the food with the entered food ID is included in the Orders.txt file of this table, the quantity information for this order must be updated. 
- However, in order for an order to be updated, this order must be active. 
- If there are two active orders with the same food ID, the first order must be updated. 

Cancel order: The table ID of the table to cancel the order and the food ID of the food to be canceled must be obtained from the customer.  

- If there is a table with the entered table ID and the food with the entered food ID is included in the Orders.txt file of this table, this order must be deactivated. 
- If there are more than one active orders with the same food ID, the first order must be cancelled. 

Pay the bill:  The table ID that will make the payment must be obtained from the customer.  

- The total cost of active orders for this table must be calculated and written to the ClosedOrders.txt file. 
- The Orders.txt file of the relevant table must be emptied. 
- Even if there is no order, the total payment amount should be recorded as 0. 
3. Common functions that both panels should have 

Display food menu: Each food information in Foods.txt should be displayed on the screen. 

Show order list of table: The table ID of the table whose order information will be shown on the screen must be obtained from the customer. Then, the order information in Orders.txt for this table should be displayed on the screen. 

Additional Information 

- We share two folders with you: Reservation Program and C files. 
- The Reservation Program folder contains the working versions of the requested softwares. 
- This assignment will be done in a group of two students. 
- The first student in the group will write the program that will perform the tasks of the Admin panel, as in the Admin.exe file. 
- The second student in the group will write a program that will perform the tasks of the Customer panel, as in the Customer.exe file. 
- The .txt files included here are default files. You can check the contents of the .txt files by running .exe files given. 
- You must send an e-mail to oayana@atu.edu.tr with information about who you will be in a group with and which student will write the Admin panel and which student will write the Customer panel, by April 7, 23.59. 
- I will randomly match students who do not provide group information. 
- If a student in the group does not submit the program assigned to him/her, he/she will directly receive a 0. 15 points will be deducted from your partner. 

Assignment Submission 

- We share .c and .h files in the C files folder. 
- Students who will write the admin panel must fill in and send the admin.c, admin.h and mainAdmin.c files. 
- Students who will write the Customer panel must fill in and send customer.c, customer.h and mainCustomer.c files. 
- .h files should contain only struct definitions, global variables and function signatures. 
- In .c files, the functions defined in .h files must be implemented and used. 
- Struct definitions, global variables and function signatures that are common to both Admin and Customer panels should be implemented in common.h and common.c files and used by including them in both programs. 
- Information about who wrote the common functions should be written above the function as a comment line. Care should be taken to write common functions equally. 
- Students within the group must submit their solutions individually. Common.c and common.h files must be included in both student files. 

IMPLEMENTATION CONSTRAINTS:   

- Standard I/O functions must be used for I/O operations (eg: fread, fwrite, fprintf, fscanf, fseek). 
- Orders.txt, TakenOrders.txt and Foods.txt files must be used in binary form. 
- log.txt and ClosedOrders.txt files must be used in the normal form. 
