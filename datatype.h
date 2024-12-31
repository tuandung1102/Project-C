// noi cac em di import nhung thu vien, khai bao struct
#include <string.h>
#include <stdbool.h>



typedef struct {
	int month,day,year;
} Date;
void showUsers();
void addUser();


typedef struct {
    int userId;
    char name[100];
    int age;
    char dateOfBirth[20];
    char email[50];
    char phone[15];
    float balance;
    char transactionHistory[10][100]; 
    int transactionCount; 
} User;
