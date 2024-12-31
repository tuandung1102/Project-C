#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
	int choice;
	do {
			printf("\t  ***Bank Management System Using C***\n\n");
	printf("\t\t   CHOOSE YOUR ROLE\n");
	printf("\t      ==========================\n");
	printf("\t      [1] Admin.\n");
	printf("\t      [2] User.\n");
	printf("\t      [0] Exit the Program.\n");
	printf("\t      ==========================\n");
	printf("\t      Enter The Choice: ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			Admin();
			break;
		case 2:
		
			break;
		case 0:
		    printf("\t      ======== Thank You ========\n");
		    printf("\t      ======= See You Soon ======\n\n");
		    printf("\t     -----------------------------\n");
			break;
		default:
			printf("Invalid selection. Please try again!\n");
	}
	 
} while (choice!=0); 
     	return 0;
}
