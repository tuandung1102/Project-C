//Noi di trien khai cac ham
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "datatype.h"
#include "function.h"

User users[100];
int userCount = 0;

int validateLogin() {
    char username[50], password[50];
    char correctUsername[] = "admin";  
    char correctPassword[] = "12345"; 

    printf("\n\t\t=== Admin Login ===\n\n");

    while (1) {
        printf("\t\tEnter Username: ");
        scanf("%s", username); 
        printf("\t\tEnter Password: ");
        scanf("%s", password); 

        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
            printf("\n\t\t Login Successful!\n");
            return 1; 
        } else {
            printf("\n\tInvalid Username or Password. Please try again.\n\n");
        }
    }
}


void Admin(){
	    if (validateLogin()) {
        printf("\n\t\t Welcome, Admin!\n\n");
       
    } else {
        printf("\n\t\t Access Denied.\n");
    }
		int choice;
		do {
			printf("\t  ***Bank Management System Using C***\n\n");
	printf("\t\t\t MENU\n");
	printf("\t      ==========================\n");
	printf("\t      [1] Add A New user.\n");
	printf("\t      [2] Show All suers.\n");
	printf("\t      [3] Show detail an user.\n");
	printf("\t      [4] Lock (Unlock) an user.\n");
	printf("\t      [5] User Guideline.\n");
	printf("\t      [6] About Us.\n");
	printf("\t      [0] Exit MENU.\n");
	printf("\t      ==========================\n");
	printf("\t      Enter The Choice: ");
	scanf("%d",&choice);
	switch(choice){
		  case 1:
		  	addUser();
		  	break;
		  case 2:
		  	loadUsersFromFile();
		  	showUsers();
		  	break;
		  case 3: 
	        playCase3();
	        break;
		  case 0:
			break;
		default:
			printf("\tInvalid selection. Please try again!\n");	
		}
} while (choice!=0);
}

void displaySearchResults(User users[], int indices[], int count);

void searchUser(User users[], int userCount) {
    char searchTerm[100];
    int indices[100];  
    int count = 0;

    printf("Nhap ten nguoi dung muon tim kiem: ");
    scanf(" %[^\n]s", searchTerm);

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchTerm) != NULL) {
            indices[count++] = i;  
        }
    }

    displaySearchResults(users, indices, count);  
}

void displaySearchResults(User users[], int indices[], int count) {
    if (count == 0) {
        printf("Khong tim thay nguoi dung nao!\n");
    } else {
    
        printf("Danh sach nguoi dung tim duoc:\n");
        printf("+------+----------------------+------+------------+-------------------------+-----------------+\n");
        printf("| ID   | Ten nguoi dung       | Tuoi | Ngay sinh  | Email                   | So dien thoai   |\n");
        printf("+------+----------------------+------+------------+-------------------------+-----------------+\n");
        
        for (int i = 0; i < count; i++) {
            printf("| %-4d | %-20s | %-4d | %-10s | %-23s | %-15s |\n",
                   users[indices[i]].userId, users[indices[i]].name, users[indices[i]].age, 
                   users[indices[i]].dateOfBirth, users[indices[i]].email, users[indices[i]].phone);
        }
        printf("+------+----------------------+------+------------+-------------------------+-----------------+\n");
    }
}

void searchUserByID(User users[], int userCount, int id);
void handleCase2(User users[], int userCount);
int findUserIndexByID(User users[], int userCount, int id);

void searchUserByID(User users[], int userCount, int id) {
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (users[i].userId == id) {
            found = 1;

            printf("\nUser Details:\n");
            printf("UserID: %d\n", users[i].userId);
            printf("Username: %s\n", users[i].name);
            printf("Email: %s\n", users[i].email);
            printf("Phone: %s\n", users[i].phone);
            printf("Balance: $%.2f\n", users[i].balance);

            if (users[i].transactionCount > 0) {
                printf("\nTransaction History:\n");
                printf("----------------------------------------\n");
                printf("| %-3s | %-30s |\n", "No", "Transaction Details");
                printf("----------------------------------------\n");
                for (int j = 0; j < users[i].transactionCount; j++) {
                    printf("| %-3d | %-30s |\n", j + 1, users[i].transactionHistory[j]);
                }
                printf("----------------------------------------\n");
            } else {
                printf("\nNo transaction history available.\n");
            }
            return;
        }
    }

    if (!found) {
        printf("\nNo user found with ID %d.\n", id);
    }
}

void handleCase2(User users[], int userCount) {
    int id;
    printf("\nEnter the User ID to search: ");
    scanf("%d", &id);
    searchUserByID(users, userCount, id);
}

int findUserIndexByID(User users[], int userCount, int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].userId == id) {
            return i;  
        }
    }
    return -1;  
}

void editUser(User users[], int userCount) {
    int id;
    printf("\nEnter the User ID to edit: ");
    scanf("%d", &id);
    int index = findUserIndexByID(users, userCount, id);

    if (index == -1) {
        printf("\nNo user found with ID %d.\n", id);
        return;
    }

    printf("\nEditing User with ID %d\n", id);
    printf("Enter new username: ");
    scanf(" %[^\n]s", users[index].name);
    printf("Enter new email: ");
    scanf(" %[^\n]s", users[index].email);
    printf("Enter new phone: ");
    scanf(" %[^\n]s", users[index].phone);
    printf("Enter new balance: ");
    scanf("%f", &users[index].balance);

    printf("\nUser updated successfully!\n");
}

void deleteUser(User users[], int *userCount) {
    int id;
    printf("\nEnter the User ID to delete: ");
    scanf("%d", &id);
    int index = findUserIndexByID(users, *userCount, id);

    if (index == -1) {
        printf("\nNo user found with ID %d.\n", id);
        return;
    }

    for (int i = index; i < *userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    (*userCount)--; 
    printf("\nUser with ID %d deleted successfully!\n", id);
}

void sortUsers(User users[], int userCount) {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (strcmp(users[i].name, users[j].name) > 0) {
               
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    printf("\nUsers sorted by username successfully!\n");
}

void playCase3() {
    int choice;
    do {
        printf("\n\t  *** Bank Management System Using C ***\n\n");
        printf("\t\t   CHOOSE YOUR ROLE\n");
        printf("\t      ==========================\n");
        printf("\t      [1] Search user by name\n");
        printf("\t      [2] Search user by ID\n");
        printf("\t      [3] Edit user\n");
        printf("\t      [4] Delete user\n");
        printf("\t      [5] Sort users by name\n");
        printf("\t      [0] Exit\n");
        printf("\t      ==========================\n");
        printf("\t      Enter The Choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                searchUser(users, userCount);
                break;

            case 2:
                handleCase2(users, userCount);
                break;

            case 3:
                 editUser(users, userCount);
                break;

            case 4:
                  deleteUser(users, &userCount);
                break;

            case 5:
                sortUsers(users, userCount);
                break;

            case 0:
                printf("Exiting User Management Menu.\n");
                break;

            default:
                printf("\nInvalid selection. Please try again!\n");
        }

    } while (choice != 0);
}

void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file de doc du lieu!\n");
        return;
    }

    while (fscanf(file, "%d|%99[^|]|%d|%19[^|]|%49[^|]|%14[^\n]\n",
                  &users[userCount].userId, 
                  users[userCount].name, 
                  &users[userCount].age, 
                  users[userCount].dateOfBirth, 
                  users[userCount].email, 
                  users[userCount].phone) == 6) {
        userCount++;
        if (userCount >= 100) {
            break;
        }
    }

    fclose(file);
}

void showUsers() {
    if (userCount == 0) {
        printf("Khong co nguoi dung nao!\n");
        return;
    }

    printf("\n--- Danh sach nguoi dung ---\n");

    printf("+-----+--------+----------------------+------------+---------------+-------------------------------+-------------------+\n");
    printf("| STT | ID     | Ten                  | Tuoi       | Ngay sinh     | Email                         | Phone             |\n");
    printf("+-----+--------+----------------------+------------+---------------+-------------------------------+-------------------+\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-3d | %-6d | %-20s | %-10d | %-13s | %-30s| %-16s  |\n",
               i + 1,
               users[i].userId,
               users[i].name,
               users[i].age,
               users[i].dateOfBirth,
               users[i].email,
               users[i].phone);  
    }

    printf("+-----+--------+----------------------+------------+---------------+-------------------------------+-------------------+\n");
}	


bool isDuplicate(int userId, const char* email, const char* phone, const char* name) {
    for (int i = 0; i < userCount; i++) {
        if (userId != -1 && users[i].userId == userId) {
            return true;  
        }
        if (strcmp(users[i].email, email) == 0) {
            return true;  
        }
        if (strcmp(users[i].phone, phone) == 0) {
            return true;  
        }
        if (strcmp(users[i].name, name) == 0) {
            return true;  
        }
    }
    return false;
}

void saveUserToFile() {
    FILE *file = fopen("users.txt", "a"); 
    if (file == NULL) {
        printf("Khong the mo file de ghi!\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%d|%s|%d|%s|%s|%s\n", 
                users[i].userId, 
                users[i].name, 
                users[i].age, 
                users[i].dateOfBirth, 
                users[i].email, 
                users[i].phone);
    }

    fclose(file);
    printf("Du lieu da duoc luu vao file users.txt\n");
}

void addUser() {
    if (userCount >= 100) {
        printf("Danh sach nguoi dung da day!\n");
        return;
    }
    printf("\n--- Them nguoi dung ---\n");

    int userId;
    while (1) {
        printf("Nhap ID (4 so): ");
        if (scanf("%d", &userId) != 1 || userId < 1000 || userId > 9999) {
            printf("Loi: Vui long nhap so nguyen hop le (4 so)!\n");
            while (getchar() != '\n'); 
        } else if (isDuplicate(userId, "", "", "")) {
            printf("Loi: ID da ton tai. Vui long nhap ID khac!\n");
        } else {
            break;
        }
    }
    getchar(); 

    char name[100];
    while (1) {
        printf("Nhap ten: ");
        scanf(" %99[^\n]", name);
        if (strlen(name) == 0 || strspn(name, " ") == strlen(name)) {
            printf("Loi: Ten khong duoc de trong! Vui long nhap ten.\n");
        } else if (isDuplicate(-1, "", "", name)) {
            printf("Loi: Ten da ton tai. Vui long nhap ten khac!\n");
        } else {
            break;
        }
    }

    int age;
    while (1) {
        printf("Nhap tuoi: ");
        if (scanf("%d", &age) != 1 || age <= 0) {
            printf("Loi: Vui long nhap so nguyen hop le cho tuoi!\n");
            while (getchar() != '\n'); 
        } else {
            break;
        }
    }
    getchar(); 

    char dateOfBirth[20];
    while (1) {
        printf("Nhap ngay sinh (DD/MM/YYYY): ");
        scanf(" %19[^\n]", dateOfBirth);
        if (strlen(dateOfBirth) == 0) {
            printf("Loi: Ngay sinh khong duoc de trong!\n");
        } else {
            break;
        }
    }

    char email[50];
    while (1) {
        printf("Nhap email: ");
        scanf(" %49[^\n]", email);
        if (strlen(email) == 0) {
            printf("Loi: Email khong duoc de trong!\n");
        } else if (isDuplicate(-1, email, "", "")) {
            printf("Loi: Email da ton tai. Vui long nhap email khac!\n");
        } else {
            break;
        }
    }

    char phone[15];
    while (1) {
        printf("Nhap phone: ");
        scanf(" %14[^\n]", phone);
        if (strlen(phone) == 0) {
            printf("Loi: So dien thoai khong duoc de trong!\n");
        } else if (isDuplicate(-1, "", phone, "")) {
            printf("Loi: So dien thoai da ton tai. Vui long nhap so dien thoai khac!\n");
        } else {
            break;
        }
    }

    users[userCount].userId = userId;
    strcpy(users[userCount].name, name);
    users[userCount].age = age;
    strcpy(users[userCount].dateOfBirth, dateOfBirth);
    strcpy(users[userCount].email, email);
    strcpy(users[userCount].phone, phone);

    userCount++;

    saveUserToFile();
    
    printf("Them nguoi dung thanh cong!\n");
}


