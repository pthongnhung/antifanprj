#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "function.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int numberOfUser;
	int length;
	int choice;
	int choose; 
	do{
		showRole();
		printf("Enter the choice: ");
		scanf("%d",&choose);
		switch(choose){
		case 1:
		do {
		menuUser();
		printf("Enter The Choice: ");
		scanf("%d", &choice);
		system("cls");
		fflush(stdin);
		switch(choice){
			case 1:
				addNewUser(&length, users, accountInfo);
				backOrexit();
				break;
			case 2:
				readUserFromFile(&length, users);
				backOrexit();
				break;
			case 3:
				searchUserName(&length, users);
				backOrexit();
			case 4:
				searchUserId(&length, users);
				backOrexit();
			case 5:
				lockoropenUser(&length, users,accountInfo);
				backOrexit();
				break;
			case 6:
				sortusersByName(&length, users);
				backOrexit();
				break;
			case 0:
				exitMenu();
				return 0;
			default:
				printf("Invalid choice! Please select again!");
		}
    	} while(choice != 0);
	  	break;
    	case 2:
		break;
    	case 0:
			exitMenu();	
	    	break;
    	default:
		printf("Loi\n");
    }
	}while(choose!=0);
	return 0; 
}

