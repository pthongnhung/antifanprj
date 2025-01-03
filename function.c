#include <stdio.h>
#include "function.h" 
#include <string.h> 
#include "datatype.h" 
#include <stdlib.h>

//logic ham
void showRole(){
    printf("*** Bank Account Management***\n");
    printf("\n");
    printf("        CHOOSE YOUR ROLE\n");
    printf("   ==============================\n"); 
    printf("        [1]. Admin\n");
    printf("        [2]. User\n");
    printf("        [0]. Exit the Program\n");
    printf("   ==============================\n");
}
void exitMenu(){
	printf("\n ========== Thank you ==========\n");
	printf("   ======= See you soon===========\n");
}
void menuUser(){
	printf("\n***** Bank Management System Using C *****\n");
    printf("   \n");
    printf("   ==============================\n"); 
    printf("           MENU      \n");
    printf("        [1] Add A New User\n");
    printf("        [2] Show All Users\n");
    printf("        [3] Search for users by name\n");
    printf("        [4] User details by ID\n");
    printf("        [5] LockUer\n");
    printf("        [6] Sort users by name\n");
    printf("        [0] Exit the Program\n");
    printf("   =================================\n");
}

void addNewUser(int *length, struct User users[],struct AccountInfo accountInfo[]) {
    int day, month, year;
    int numberOfUser;
    int gender;
    char email[50];
    char fileName[20]="BankUser.bin";
    printf("\nEnter the number of users you want to add: ");
    scanf("%d", &numberOfUser);
    getchar();  // Consume newline character
    printf("\t      Add A New User \n");

    for (int i = *length; i < (*length + numberOfUser); i++) {
        printf("\nEnter account number information %d:\n", i + 1);
           getchar();
        do {
            printf("Enter the ID (10 characters): ");
            fgets(users[i].userId, sizeof(users[i].userId), stdin);
            users[i].userId[strcspn(users[i].userId, "\n")] = '\0';
            if(strlen(users[i].userId) != 10){
            	printf("Invalid ID! It must be 10 characters long.\n");
			}	 
        } while ( strlen(users[i].userId) != 10);

        printf("Enter the name: ");
        fgets(users[i].name, sizeof(users[i].name), stdin);
        users[i].name[strcspn(users[i].name, "\n")] = '\0';

        do {
            printf("Enter the email: ");
        	fgets(email, sizeof(email), stdin);
        	email[strcspn(email, "\n")] = '\0'; 
    	} while (!isValidEmail(email) );
		strcpy(users[i].email, email);

        do {
            printf("Enter the phone (10 characters): ");
            fgets(users[i].phone, sizeof(users[i].phone), stdin);
            users[i].phone[strcspn(users[i].phone, "\n")] = '\0';
        } while ( strlen(users[i].phone) != 10 );

        do {
            printf("Enter gender (male=1, female=0): ");
            scanf("%d", &users[i].gender);
        } while (users[i].gender != 0 && users[i].gender != 1);

        do {
            printf("Enter birthdate:\n");
            printf("    Enter day: ");
            scanf("%d", &day);
            printf("    Enter month: ");
            scanf("%d", &month);
            printf("    Enter year: ");
            scanf("%d", &year);
            getchar();  // Consume newline character
        } while (!isValidDate(day, month, year));

        users[i].dateOfBirth.day = day;
        users[i].dateOfBirth.month = month;
        users[i].dateOfBirth.year = year;

        
       	printf("Enter the username: ");
        fgets(users[i].username, sizeof(users[i].username), stdin);
        users[i].username[strcspn(users[i].username, "\n")] = '\0';
		

       do{
       	   printf("Enter the balance: ");
           scanf("%lf", &accountInfo[i].balance);
           if(accountInfo[i].balance<0){
           	printf("Account balance must not be negative\n");
		   }
	    } while(accountInfo[i].balance<0);
        accountInfo[i].status=1;  // Default status is active (1)
        printf("User added successfully!\n");
    }

    saveUserToFile(users, *length + numberOfUser);  // Save the new users to the file
    *length += numberOfUser;  // Update the length of the user array
    

}
void backOrexit(){
	char choice2;
    do {
        printf("\nGo back(b)? or Exit(0)?: ");
        scanf(" %c", &choice2);
        if (choice2 == 'b') {
            return;
        } else if (choice2 == '0') {
            printf("Exiting...\n");
            exit(0);
        }
    } while (choice2 != 'b' && choice2 != '0');
}
void saveUserToFile(struct User users[], int length) {
    FILE *file = fopen("BankUser.bin", "wb");
    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }
    fwrite(users, sizeof(struct User), length, file);  // Ghi ?úng s? l??ng user
    fclose(file);
    printf("Data saved successfully!\n");
}

bool isValidEmail(char *email) {
    return (strlen(email) > 0 && strchr(email, '@') != NULL);
}
bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) return false;
        } else {
            if (day > 28) return false;
        }
    }
    return true;
}

void readUserFromFile(int *length, struct User users[]){
	FILE *file = fopen("BankUser.bin", "rb");
	if(file == NULL){
		printf("Error opening file\n");
	}
	 *length = fread(users, sizeof(struct User), 100, file);
    if(*length == 0){
        printf("No data found...\n");
    }else{
        printf("Read %d user from file\n", *length);
    }
   
    printf("|==================================================================================|\n");
    printf("                            Thong tin Nguoi Dung\n");
    printf("|==================================================================================|\n");
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    printf("| User ID    | Name               | Status   | Phone      | Email                  |\n");
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    for (int i = 0; i < *length; i++) {
        printf("| %-10s | %-18s | %-8s | %-10s | %-22s |\n",users[i].userId,users[i].name,accountInfo[i].status ? "open" : "lock",users[i].phone,users[i].email);
    }
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    printf("\n");
    fclose(file);
    saveUserToFile(users, *length);
}


void cleanString(char *str) {
    int i = 0;
    while (str[i]) {
        if (!isprint((unsigned char)str[i])) {
            str[i] = '\0';  
        }
        i++;
    }
}

void searchUserName(int *length, struct User users[]) {
	char fullName[20];
    bool found = false;
    printf("Enter the name to search: ");
    fgets(fullName, sizeof(fullName), stdin);
    fullName[strcspn(fullName, "\n")] = '\0';

    FILE *file = fopen("BankUser.bin", "rb");
	if(file == NULL){
		printf("Error opening file\n");
	}
	 *length = fread(users, sizeof(struct User), 100, file);
    if(*length == 0){
        printf("No data found...\n");
    }else{
        printf("Read %d user from file\n", *length);
    }
   
    printf("|==================================================================================|\n");
    printf("                            Thong tin Nguoi Dung\n");
    printf("|==================================================================================|\n");
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    printf("| User ID    | Name               | Status   | Phone      | Email                  |\n");
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    for (int i = 0; i < *length; i++) {
    	if(strstr(users[i].name,fullName)){
           printf("| %-10s | %-18s | %-8s | %-10s | %-22s |\n",users[i].userId,users[i].name,accountInfo[i].status ? "open" : "lock",users[i].phone,users[i].email);
           found = true;
        }
    }
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    printf("\n");
    
    if (!found) {
        printf("No user found matching the fullName: %s\n", fullName);
    }
    fclose(file);

}
void searchUserId(int *length, struct User users[]) {
    bool found = false;
    char fullId[20];
    printf("Enter the Id to search: ");
    fgets(fullId, sizeof(fullId), stdin);
    fullId[strcspn(fullId, "\n")] = '\0';

    FILE *file = fopen("BankUser.bin", "rb");
	if(file == NULL){
		printf("Error opening file\n");
	}
	 *length = fread(users, sizeof(struct User), 100, file);
    if(*length == 0){
        printf("No data found...\n");
    }else{
        printf("Read %d user from file\n", *length);
    }
    printf("\n+------------+------------------+--------+------------+----------------+------------+----------+--------+\n");
    printf("|   ID       |       Name       | Gender | Birth Date |   User Name    |   Phone    | Balance  | Status |\n");
    printf("+------------+------------------+--------+------------+----------------+------------+----------+--------+\n");
    for (int i = 0; i < *length; i++) {
        if (strcmp(users[i].userId, fullId)==0) {
            printf("| %-10s | %-16s | %-6s | %02d/%02d/%04d | %-14s | %-10s | %-8.2f | %-6s |\n",
            users[i].userId,  users[i].name, users[i].gender?"male":"female",
		    users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year,
		    users[i].username,  users[i].phone, accountInfo[i].balance,
            accountInfo[i].status ? "open" : "lock");
           found = true;
        }
    printf("+------------+------------------+--------+------------+----------------+------------+----------+--------+\n");
    printf("\n");
    }
    if (!found) {
        printf("No user found matching the fullId: %s\n", fullId);
    }
    fclose(file);
  
}
void lockoropenUser(int *length, struct User users[],struct AccountInfo accountInfo[]){
	bool found = false;
    char fullId[20];
    int choose1; 
    printf("Enter the Id to search: ");
    fgets(fullId, sizeof(fullId), stdin);
    fullId[strcspn(fullId, "\n")] = '\0';

    FILE *file = fopen("BankUser.bin", "rb");
	if(file == NULL){
		printf("Error opening file\n");
	}
	 *length = fread(users, sizeof(struct User), 100, file);
    if(*length == 0){
        printf("No data found...\n");
    }
    for (int i = 0; i < *length; i++) {
        if (strcmp(users[i].userId, fullId)==0) {
        	if(accountInfo[i].status=1){
        		 printf("The user is unlocked\n");
        		 printf("Do you want to lock the user?\n");
        		 printf("1: Yes, 2:No\n");
        		 scanf("%d",&choose1);
                 if(choose1==1){
                 	accountInfo[i].status=0; 
                    found = true;
                    printf("User locked!!!\n");
				 }
				   saveUserToFile(users, *length);
			}else{
				 printf("User is locked\n");
				 printf("Do you want to unlocked the user?\n");
        		 printf("1: Yes, 2:No\n");
                 if(choose1==1){
                    accountInfo[i].status=1; 
                    found = true;
                    printf("User unlocked!!!\n");
				 }
				 saveUserToFile(users, *length);
			} 
        }
        
   }
    if (!found) {
        printf("No user found matching the fullId: %s\n", fullId);
    }
    fclose(file);
   
}
void SwapUser(struct User *a, struct User *b) {
    struct  User temp = *a;
    *a = *b;
    *b = temp;
}

void sortusersByName(int *length, struct User users[]) {
	int choice1;
    printf("\n*** Sort Users by Name ***\n");
    printf("1. Sort in ascending order (A-Z)\n");
    printf("2. Sort in descending order (Z-A)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice1);
    FILE *file = fopen("BankUser.bin", "rb");
	if(file == NULL){
		printf("Error opening file\n");
	}
	 *length = fread(users, sizeof(struct User), 100, file);
    if(*length == 0){
        printf("No data found...\n");
    }
    for (int i = 0; i < *length - 1; i++) {
        for (int j = i + 1; j < *length; j++) {
            if (choice1 == 1 && strcmp(users[i].name, users[j].name) > 0) {
                SwapUser(&users[i], &users[j]);
            } else if (choice1 == 2 && strcmp(users[i].name, users[j].name) < 0) {
                SwapUser(&users[i], &users[j]);
            }
        }
    }
    printf("\nUsers have been sorted successfully!\n");
    printf("\nSorted User List:\n");
    printf("|==================================================================================|\n");
    printf("                            Thong tin Nguoi Dung\n");
    printf("|==================================================================================|\n");
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    printf("| User ID    | Name               | Status   | Phone      | Email                  |\n");
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    for (int i = 0; i < *length; i++) {
           printf("| %-10s | %-18s | %-8s | %-10s | %-22s |\n",users[i].userId,users[i].name,accountInfo[i].status ? "open" : "lock",users[i].phone,users[i].email);
    }
    printf("+------------+--------------------+----------+------------+------------------------+\n");
    printf("\n");
    fclose(file);
    
}
