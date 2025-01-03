
#include "datatype.h"
//nguyen mau ham
void showRole();
void menuUser();
void exitMenu();
void addNewUser(int *length, struct User users[],struct AccountInfo accountInfo[]);
void backOrexit();
void saveUserToFile(struct User users[], int length);
void readUserFromFile(int *length, struct User users[]);
bool isValidDate(int day, int month, int year);
bool isValidEmail(char *email);
void searchUserName(int *length, struct User users[]);
void searchUserId(int *length, struct User users[]);
void lockoropenUser(int *length, struct User users[],struct AccountInfo accountInfo[]);
void SwapUser(struct User *a, struct User *b);
void sortusersByName(int *length, struct User users[]);

