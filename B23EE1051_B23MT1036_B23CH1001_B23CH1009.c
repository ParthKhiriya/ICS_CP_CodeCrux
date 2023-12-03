// Group Name : CodeCrux
// Members : Parth Khiriya(B23EE1051) , Sambhav Jha(B23MT1036) , Arush Aaron John(B23CH1009) , Abhyudaya Tiwari(B23CH1001) 
// To know about the correct PINs, please check the "userdata.txt" file to know that which PINs are correct.

#include <stdio.h>
#include <stdlib.h>
#define FILENAME "C:/C Tutorial/userdata.txt"

void printATM() {
    printf("             _______    __  __  \n");
    printf("     /\\     |__   __|  |  \\/  |\n");
    printf("    /  \\       | |     | \\  / |\n");
    printf("   / /\\ \\      | |     | |\\/| |\n");
    printf("  / ____ \\     | |     | |  | |\n");
    printf(" /_/    \\_\\    |_|     |_|  |_|\n");
    printf("                               \n");
    printf("\n");
}
void end(){
    printf(" _______ _                 _           __                   _     _ _   _              \n");
    printf("|__   __| |               | |         / _|                 (_)   (_) | (_)             \n");
    printf("   | |  | |__   __ _ _ __ | | _____  | |_ ___  _ __  __   ___ ___ _| |_ _ _ __   __ _  \n");
    printf("   | |  | '_ \\ / _` | '_ \\| |/ / __| |  _/ _ \\| '__| \\ \\ / / / __| | __| | '_ \\ / _` | \n");
    printf("   | |  | | | | (_| | | | |   <\\__ \\ | || (_) | |     \\ V /| \\__ \\ | |_| | | | | (_| | \n");
    printf("   |_|  |_| |_|\\__,_|_| |_|_|\\_\\___/ |_| \\___/|_|      \\_/ |_|___/_|\\__|_|_| |_|\\__, | \n");
    printf("                                                                                  __/| \n");
    printf("                                                                                 |___/  \n");
}
struct User {
    int pin;
    int balance;
};
int numof(int a){
   int d=0;
    while(a>0){
        d++;
        a=a/10;
    }
    return d+1;
}
void updateUserBalance(int pin, int updatebal) {
    FILE *file;
    file = fopen(FILENAME, "r+");
    int tempPin, tempBalance;

    if (file != NULL) {
        while (fscanf(file, "%d,%d", &tempPin, &tempBalance) == 2) {
            if (tempPin == pin) {

                fseek(file, -4 - numof(tempBalance), SEEK_CUR); // Move back to the start of the line
                fprintf(file, "%d,%d",tempPin ,updatebal); // Update balance
                fclose(file);
                return;   
            }
        }

        fclose(file);
        printf("PIN not found while updating balance.\n");
    } else {
        printf("Error opening file.\n");
    }
} 


int main() {
    int pin, amount;
    struct User currentUser;  
    printATM();

    printf("Enter your PIN: ");
    scanf("%d", &pin);

    FILE *file;
    file = fopen("userdata.txt", "r");

    int f = 0;
    int p = 0; // Initialize attempts counter

    while (p < 3) {
        file = fopen(FILENAME, "r");
        int f = 0;
        if (file != NULL) {
            while (fscanf(file, "%d,%d", &currentUser.pin, &currentUser.balance) == 2) {
                if (currentUser.pin == pin) {
                    f = 1;
                    break;
                }
            }
            fclose(file);
        }
        else {
            printf("Error opening file.\n");
            return 1;
        }

        if (f) {
            printf("PIN found. Welcome!\n");

            int choice;
            while (1) {
                printf("*<__________ATM__________>*\n");
                printf("|  1) Check Balance      |\n");
                printf("|  2) Withdraw Cash      |\n");
                printf("|  3) Deposit Cash       |\n");
                printf("|  4) Exit               |\n");
                printf("|   Enter your choice:   ");
                

                scanf("%d", &choice);
                printf("|________________________|");
                system("cls"); 

                switch (choice) {
                    case 1:
                        printf("Your balance is %d\n\n", currentUser.balance);
                        break;

                    case 2:
                        printf("Enter amount to be withdrawn: ");
                        scanf("%d", &amount);
                        if (amount > 0 && amount <= currentUser.balance) {
                            printf("You have withdrawn %d\n", amount);
                            currentUser.balance -= amount;
                            printf("Your updated balance is %d\n", currentUser.balance);
                            updateUserBalance(pin, currentUser.balance);
                        } else {
                            printf("Invalid amount or insufficient funds\n");
                        }
                        break;

                    case 3:
                        printf("Enter amount to be deposited: ");
                        scanf("%d", &amount);
                        if (amount > 0) {
                            printf("Successfully deposited %d\n", amount);
                            currentUser.balance += amount;
                            printf("Your updated balance is %d\n", currentUser.balance);
                            updateUserBalance(pin, currentUser.balance);
                        } else {
                            printf("Invalid amount\n");
                        }
                        break;

                    case 4:
                        //printf("Thank you for visiting.\n");
                        end();
                        return 0;

                    default:
                        printf("Invalid choice\n");
                }
            }
            break; // Exit the loop after successful login
        } 
        else {
            p++;
            if (p < 3) {
                printf("PIN not found. Access denied. Attempts left: %d\n", 3 - p);
                printf("Enter your PIN again: ");
                scanf("%d", &pin);
            } 
            else {
                printf("Maximum attempts reached. Exiting...\n");
                break; // Exit the loop after 3 attempts
            }
        }
    }

    return 0;
}
