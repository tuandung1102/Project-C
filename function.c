//Noi di trien khai cac ham
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "datatype.h"
#include "function.h"
#include <ctype.h>
#include <conio.h> // Dành cho getch() de xu ly nhap mat khau


char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack; 
    
    for ( ; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h = haystack;
            const char *n = needle;
            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                h++;
                n++;
            }
            if (!*n) return (char *)haystack; 
        }
    }
    return NULL; 
}

User users[100];
int userCount = 0;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void searchUser(FILE *file) {
    User users[100];
    int userCount = 0;
    char searchTerm[100];
    int indices[100];
    int count = 0;

    rewind(file);
    while (fread(&users[userCount], sizeof(User), 1, file) == 1) {
        userCount++;
        if (userCount >= 100) break;
    }

    while (1) {  
        printf("Nhap ten nguoi dung muon tim kiem (hoac nhap 'exit' de thoat): ");
        scanf(" %[^\n]s", searchTerm);

        if (strcmp(searchTerm, "exit") == 0) break;

        toLowerCase(searchTerm);  

        count = 0;  
       
        for (int i = 0; i < userCount; i++) {
            char tempName[100];
            strcpy(tempName, users[i].name);
            toLowerCase(tempName);

            if (strstr(tempName, searchTerm) != NULL) {
                indices[count++] = i;
            }
        }

        displaySearchResults(users, indices, count);
    }
}

void displaySearchResults(User users[], int indices[], int count) {
    if (count == 0) {
        printf("Khong tim thay nguoi dung nao!\n");
    } else {
        printf("\t\tDanh sach nguoi dung tim duoc:\n");
        printf("+----------+----------------------+------+------------+-------------------------+-----------------+\n");
        printf("| ID       | Ten nguoi dung       | Tuoi | Ngay sinh  | Email                   | So dien thoai   |\n");
        printf("+----------+----------------------+------+------------+-------------------------+-----------------+\n");
        
        for (int i = 0; i < count; i++) {
            printf("| %-8s | %-20s | %-4d | %-10s | %-23s | %-15s |\n",
                   users[indices[i]].userId, users[indices[i]].name, users[indices[i]].age, 
                   users[indices[i]].dateOfBirth, users[indices[i]].email, users[indices[i]].phone);
        }
        printf("+----------+----------------------+------+------------+-------------------------+-----------------+\n");
    }
}


void searchUserByID(const char *filename, const char *id) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("\n\tUnable to open file for reading.\n");
        return;
    }

    User tempUser;
    int found = 0;

    while (fread(&tempUser, sizeof(User), 1, file) == 1) {
        if (strcmp(tempUser.userId, id) == 0) {  
            found = 1;
            printf("\nUser Details:\n");
            printf("UserID: %s\n", tempUser.userId);
            printf("Name: %s\n", tempUser.name);
            printf("Email: %s\n", tempUser.email);
            printf("Phone: %s\n", tempUser.phone);

            if (tempUser.transactionCount > 0) {
                printf("\nTransaction History:\n");
                for (int j = 0; j < tempUser.transactionCount; j++) {
                    printf("Transaction %d: %s\n", j + 1, tempUser.transactionHistory[j]);
                }
            } else {
                printf("\nNo transaction history available.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\n\tNo user found with ID %s.\n", id);
    }

    fclose(file);
}

void handleCase2(const char *filename) {
    char id[10];
    printf("\nEnter the User ID to search: ");
    scanf("%s", id);

    searchUserByID(filename, id);
}

void editUser(FILE *file) {
    User users[100];
    int userCount = 0;
    char id[10];
    int found = 0;

    rewind(file);
    while (fread(&users[userCount], sizeof(User), 1, file) == 1) {
        userCount++;
    }

    printf("Nhap Id nguoi dung muon chinh sua: ");
    scanf("%s", id);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, id) == 0) {
            found = 1;
            printf("Nhap ten moi: ");
            scanf(" %[^\n]s", users[i].name);
            printf("Nhap tuoi moi: ");
            scanf("%d", &users[i].age);
            printf("Nhap ngay sinh moi (YYYY-MM-DD): ");
            scanf("%s", users[i].dateOfBirth);
            printf("Nhap email moi: ");
            scanf("%s", users[i].email);
            printf("Nhap so dien thoai moi: ");
            scanf("%s", users[i].phone);
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay nguoi dung voi ID %s\n", id);
        return;
    }

    freopen("users.bin", "wb", file);
    if (file == NULL) {
        printf("Khong the mo tep de ghi.\n");
        return;
    }

    fwrite(users, sizeof(User), userCount, file);
    fclose(file);

    printf("Thong tin nguoi dung da duoc cap nhat\n");
}

void deleteUser(FILE *file) {
    User users[100];
    int userCount = 0;
    char id[10];
    int found = 0;

    rewind(file);
    while (fread(&users[userCount], sizeof(User), 1, file) == 1) {
        userCount++;
    }

    printf("Nhap Id nguoi dung muon xoa: ");
    scanf("%s", id);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, id) == 0) {
            found = 1;
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay nguoi dung voi ID %s\n", id);
        return;
    }

    freopen("users.bin", "wb", file);
    if (file == NULL) {
        printf("Khong the mo tep de ghi.\n");
        return;
    }

    fwrite(users, sizeof(User), userCount, file);
    fclose(file);

    printf("Nguoi dung da duoc xoa\n");
}

void sortUsers(FILE *file) {
    User users[100];
    int userCount = 0;

    rewind(file);
    while (fread(&users[userCount], sizeof(User), 1, file) == 1) {
        userCount++;
    }

    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            if (strcmp(users[j].name, users[j + 1].name) > 0) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    freopen("users.bin", "wb", file);
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
    printf("Danh sach nguoi dung da duoc sap xep.\n");
} 

void sortUsersByID(FILE *file) {
    User users[100];
    int userCount = 0;

    rewind(file);
    while (fread(&users[userCount], sizeof(User), 1, file) == 1) {
        userCount++;
    }

    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            if (strcmp(users[j].userId, users[j + 1].userId) > 0) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    freopen("users.bin", "wb", file);
    if (file == NULL) {
        printf("Khong the mo file de ghi\n");
        return;
    }

    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
    printf("Danh sach nguoi dung da duoc sap xep theo ID\n");
}


void playCase3() {
    int choice;
    FILE *file = fopen("users.bin", "r+b");
    if (file == NULL) {
        printf("\n\tUnable to open file.\n");
        return;
       
    }
    do {
        printf("\n\t  *** Bank Management System Using C ***\n\n");
        printf("\t\t   CHOOSE YOUR ROLE\n");
        printf("\t      ==========================\n");
        printf("\t      [1] Search user by name\n");
        printf("\t      [2] Search user by ID\n");
        printf("\t      [3] Edit user\n");
        printf("\t      [4] Delete user\n");
        printf("\t      [5] SortusersByName\n");
        printf("\t      [6] SortUsersByID\n");
        printf("\t      [0] Exit\n");
        printf("\t      ==========================\n");
        printf("\t      Enter The Choice: ");
        scanf("%d", &choice);
        system("cls");
        printf("\n");

        switch (choice) {
            case 1:
                searchUser(file);
                break;
            case 2:
                handleCase2("users.bin");
                break;
            case 3:
                editUser(file);
                break;
            case 4:
                deleteUser(file);  
                break;
            case 5:
                sortUsers(file);
                break;
            case 6:
            	sortUsersByID(file);  
                break;
            case 0:
                printf("\tExiting User Management Menu.\n");
                break;
            default:
                printf("\n  Invalid selection. Please try again!\n");
        }
    } while (choice != 0);
    fclose(file);
}

void saveUsersToFile(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error saving users to file.\n");
        return;
    }
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

void loadUsersFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No existing user data found.\n");
        return;
    }
    userCount = fread(users, sizeof(User), 100, file);
    fclose(file);
}

void lockUnlockUser(const char *filename) {
    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        printf("\n\t\tKhong the mo file hoac file khong ton tai!\n");
        return;
    }

    char userId[5];
    bool userFound = false;
    printf("Nhap ID nguoi dung muon khoa/mo khoa: ");
    fgets(userId, sizeof(userId), stdin);
    userId[strcspn(userId, "\n")] = '\0'; 

    User users[100];
    int userCount = fread(users, sizeof(User), 100, file);
    fclose(file);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            userFound = true;
        
            if (users[i].isLocked) {
                printf("Nguoi dung %s dang bi khoa. Ban muon mo khoa khong? (y/n): ", userId);
                char choice;
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    users[i].isLocked = false;
                    printf("Nguoi dung %s da duoc mo khoa thanh cong!\n", userId);
                } else {
                    printf("Khong thay doi trang thai khoa.\n");
                }
            } else {
                printf("Nguoi dung %s dang duoc mo. Ban muon khoa khong? (y/n): ", userId);
                char choice;
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    users[i].isLocked = true;
                    printf("Nguoi dung %s da bi khoa thanh cong!\n", userId);
                } else {
                    printf("Khong thay doi trang thai khoa.\n");
                }
            }
            break;
        }
    }

    if (!userFound) {
        printf("ID nguoi dung khong ton tai!\n");
        return;
    } 

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("\n\t\tKhong the mo file de luu!\n");
        return;
    }

    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

//doc file de lay tk mk admin
int readCredentials(char *correctUsername, char *correctPassword) {
    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        printf("\nError: Unable to open credentials file.\n");
        return 0;
    }
    fscanf(file, "%s %s", correctUsername, correctPassword);
    fclose(file);
    return 1;
}

// Ham nhap mat khau voi dau *
void inputPassword(char *password) {
    char ch;
    int i = 0;
    while ((ch = getch()) != '\r') { // '\r' la ky tu Enter
        if (ch == '\b' && i > 0) {  // Xu ly phim Backspace
            printf("\b \b");
            i--;
        } else if (ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

// Ham xac thuc dang nhap
int validateLogin() {
    char username[50], password[50];
    char correctUsername[50], correctPassword[50];

    if (!readCredentials(correctUsername, correctPassword)) {
        return 0; // Thoat neu k doc dc file
    }

    printf("\n\t\t=== Admin Login ===\n\n");

    while (1) {
        printf("\t\tEnter Username: ");
        scanf("%s", username);
        printf("\t\tEnter Password: ");
        inputPassword(password);

        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
            printf("\n\t\t Login Successful!\n");
            return 1;
        } else {
            printf("\n\tInvalid Username or Password. Please try again.\n\n");
        }
    }
}

void Admin() {
    if (validateLogin()) {
        printf("\n\t\t Welcome, Admin!\n\n");

        // Kiem tra file co ton tai hay khong
        FILE *file = fopen("admin.txt", "r");
        if (file == NULL) {
            printf("\n\tError: Cannot find the file '%s'. Exiting program.\n", "admin.txt");
            return; // Ket thuc ham neu file k ton tai
        }
        fclose(file); // Dong file sau khi kiem tra

        int choice;
        do {
            printf("\t  ***Bank Management System Using C***\n\n");
            printf("\t\t\t MENU\n");
            printf("\t      ==========================\n");
            printf("\t      [1] Add A New user.\n");
            printf("\t      [2] Show All users.\n");
            printf("\t      [3] Show detail an user.\n");
            printf("\t      [4] Lock (Unlock) an user.\n");
            printf("\t      [5] User Guideline.\n");
            printf("\t      [6] About Us.\n");
            printf("\t      [0] Exit MENU.\n");
            printf("\t      ==========================\n");
            printf("\t      Enter The Choice: ");
            scanf("%d", &choice);
            getchar(); // Xoa nho dem
            system("cls");
            switch (choice) {
                case 1:
                    addUser();
                    break;
                case 2:
                    showUsers("users.bin");
                    break;
                case 3:
                    playCase3();
                    break;
                case 4:
                    lockUnlockUser("users.bin");
                    break;
                case 0:
                    break;
                default:
                    printf("\tInvalid selection. Please try again!\n");
            }
        } while (choice != 0);
    } else {
        printf("\n\t\t Access Denied.\n");
    }
}


void showUsers(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("\n\t\tKhong the mo tep hoac tep khong ton tai!\n");
        return;
    }

    User users[100];
    int userCount = fread(users, sizeof(User), 100, file);
    fclose(file);

    if (userCount == 0) {
        printf("\t\tKhong co nguoi dung nao!\n\n");
        return;
    }

    printf("\n\t\t  --- Danh sach nguoi dung ---\n");
    printf("+-----+--------+----------------------+-----+------------+--------------------------+---------------+\n");
    printf("| STT | ID     | Ten                  | Tuoi| Ngay sinh  | Email                    | Phone         |\n");
    printf("+-----+--------+----------------------+-----+------------+--------------------------+---------------+\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-3d | %-6s |%-22s| %-4d| %-10s | %-24s | %-13s |\n",
               i + 1,
               users[i].userId,
               users[i].name,
               users[i].age,
               users[i].dateOfBirth,
               users[i].email,
               users[i].phone);
    }

    printf("+-----+--------+----------------------+-----+------------+--------------------------+---------------+\n");
}

bool isDuplicate(const char *userId, const char *email, const char *phone) {
    for (int i = 0; i < userCount; i++) {
        if ((userId && strcmp(users[i].userId, userId) == 0) ||
            (email && strcmp(users[i].email, email) == 0) ||
            (phone && strcmp(users[i].phone, phone) == 0)) {
            return true;
        }
    }
    return false;
}


bool isValidDate(const char *date) {
    int day, month, year;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) return false;
    if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2) {
        bool leapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if ((leapYear && day > 29) || (!leapYear && day > 28)) return false;
    }
    return true;
}

bool isValidEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return at != NULL && dot != NULL && at < dot;
}

bool isValidPhone(const char *phone) {
    if (strlen(phone) < 10 || strlen(phone) > 14) return false;
    for (int i = 0; phone[i]; i++) if (!isdigit(phone[i])) return false;
    return true;
}

void addUser() {
    
    loadUsersFromFile("users.bin");

    if (userCount >= 100) {
        printf("User list is full!\n");
        return;
    }

    User newUser;
    printf("\n--- Add User ---\n");

    while (1) {
        printf("Enter User ID (4 characters): ");
        fgets(newUser.userId, sizeof(newUser.userId), stdin);
        newUser.userId[strcspn(newUser.userId, "\n")] = '\0';
        if (strlen(newUser.userId) != 4 || isDuplicate(newUser.userId, NULL, NULL)) {
            printf("Invalid or duplicate ID. Please try again!\n");
        } else {
            break;
        }
    }

    printf("Enter Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';

    while (1) {
        printf("Enter Age: ");
        char ageInput[10];
        fgets(ageInput, sizeof(ageInput), stdin);
        ageInput[strcspn(ageInput, "\n")] = '\0';
        if (sscanf(ageInput, "%d", &newUser.age) != 1 || newUser.age <= 0) {
            printf("Invalid age. Please enter a valid number!\n");
        } else {
            break;
        }
    }

    printf("Enter Date of Birth (dd/mm/yyyy): ");
    fgets(newUser.dateOfBirth, sizeof(newUser.dateOfBirth), stdin);
    newUser.dateOfBirth[strcspn(newUser.dateOfBirth, "\n")] = '\0';
    while (!isValidDate(newUser.dateOfBirth)) {
        printf("Invalid date. Enter again (dd/mm/yyyy): ");
        fgets(newUser.dateOfBirth, sizeof(newUser.dateOfBirth), stdin);
        newUser.dateOfBirth[strcspn(newUser.dateOfBirth, "\n")] = '\0';
    }

    printf("Enter Email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = '\0';
    while (!isValidEmail(newUser.email) || isDuplicate(NULL, newUser.email, NULL)) {
        printf("Invalid or duplicate email. Please enter again: ");
        fgets(newUser.email, sizeof(newUser.email), stdin);
        newUser.email[strcspn(newUser.email, "\n")] = '\0';
    }

    printf("Enter Phone: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = '\0';
    while (!isValidPhone(newUser.phone) || isDuplicate(NULL, NULL, newUser.phone)) {
        printf("Invalid or duplicate phone number. Please enter again: ");
        fgets(newUser.phone, sizeof(newUser.phone), stdin);
        newUser.phone[strcspn(newUser.phone, "\n")] = '\0';
    }

    newUser.balance = 0.0;
    newUser.transactionCount = 0;

    users[userCount++] = newUser;

    saveUsersToFile("users.bin");

    printf("User successfully added!\n");
}

