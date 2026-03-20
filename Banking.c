#include <stdio.h>
#include <stdlib.h>

struct Account {
    int acc_num;
    char name[50];
    float balance;
};

struct Account a[100];
int count = 0;

void loadFile() {
    FILE *fp = fopen("bank.txt", "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%d %s %f",
                  &a[count].acc_num,
                  a[count].name,
                  &a[count].balance) != EOF) {
        count++;
    }

    fclose(fp);
}


void saveFile() {
    FILE *fp = fopen("bank.txt", "w");
    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %.2f\n",
                a[i].acc_num,
                a[i].name,
                a[i].balance);
    }

    fclose(fp);
}


int duplicateAcc(int acc) {
    for (int i = 0; i < count; i++) {
        if (a[i].acc_num == acc)
            return 1;
    }
    return 0;
}


void createAccount() {
    if (count >= 100) {
        printf("Storage Full!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &a[count].acc_num);

    if (duplicateAcc(a[count].acc_num)) {
        printf("Account already exists!\n");
        return;
    }

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", a[count].name);

    a[count].balance = 0;

    count++;
    saveFile();

    printf("Account Created Successfully\n");
}

void depositMoney() {
    int acc;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    printf("Enter Amount: ");
    scanf("%f", &amount);

    for (int i = 0; i < count; i++) {
        if (a[i].acc_num == acc) {
            a[i].balance += amount;
            printf("Updated Balance: %.2f\n", a[i].balance);
            saveFile();
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found\n");
}


void withdrawMoney() {
    int acc;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    printf("Enter Amount: ");
    scanf("%f", &amount);

    for (int i = 0; i < count; i++) {
        if (a[i].acc_num == acc) {
            found = 1;

            if (a[i].balance >= amount) {
                a[i].balance -= amount;
                printf("Remaining Balance: %.2f\n", a[i].balance);
                saveFile();
            } else {
                printf("Insufficient Balance\n");
            }
            break;
        }
    }

    if (!found)
        printf("Account Not Found\n");
}


void checkBalance() {
    int acc, found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    for (int i = 0; i < count; i++) {
        if (a[i].acc_num == acc) {
            printf("Balance: %.2f\n", a[i].balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found\n");
}


int main() {
    int choice;

    loadFile();

    while (1) {
        printf("\n------ Banking System ------\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5:
                saveFile();
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
