#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOX_WIDTH 54

// Account structure
typedef struct
{
    int accountNumber;
    int pin;
    float balance;
} Account;


// ==================== UI FUNCTIONS ====================

void clearScreen()
{
    system("cls");
}

void printBorder()
{
    for (int i = 0; i < BOX_WIDTH; i++)
    {
        printf("+");
    }

    printf("\n");
}

void printEmptyLine()
{
    printf("+");

    for (int i = 0; i < BOX_WIDTH - 2; i++)
    {
        printf(" ");
    }

    printf("+\n");
}

void printCentered(const char *text)
{
    int length = strlen(text);

    if (length > BOX_WIDTH - 2)
    {
        length = BOX_WIDTH - 2;
    }

    int leftSpaces = (BOX_WIDTH - 2 - length) / 2;
    int rightSpaces = BOX_WIDTH - 2 - length - leftSpaces;

    printf("+");

    for (int i = 0; i < leftSpaces; i++)
    {
        printf(" ");
    }

    printf("%.*s", length, text);

    for (int i = 0; i < rightSpaces; i++)
    {
        printf(" ");
    }

    printf("+\n");
}

void waitForEnter()
{
    int ch;

    // Clear remaining input
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }

    printf("\n        Press ENTER to continue...");

    getchar();
}


// ==================== ATM FUNCTIONS ====================

int authenticateUser(Account *account)
{
    int enteredPin;
    int attempts = 0;

    while (attempts < 3)
    {
        clearScreen();

        printBorder();
        printEmptyLine();
        printCentered("WELCOME TO C ATM SIMULATOR");
        printEmptyLine();
        printCentered("Please Enter Your PIN");
        printEmptyLine();
        printBorder();

        printf("\n        PIN: ");
        scanf("%d", &enteredPin);

        if (enteredPin == account->pin)
        {
            printf("\n        Login Successful!");

            waitForEnter();

            return 1;
        }

        attempts++;

        printf("\n        Incorrect PIN!");

        if (attempts < 3)
        {
            printf("\n        Attempts remaining: %d", 3 - attempts);
            waitForEnter();
        }
    }

    clearScreen();

    printBorder();
    printEmptyLine();
    printCentered("ACCOUNT BLOCKED");
    printEmptyLine();
    printCentered("Too Many Incorrect Attempts");
    printEmptyLine();
    printBorder();

    return 0;
}


void checkBalance(Account *account)
{
    char message[100];

    clearScreen();

    printBorder();
    printEmptyLine();
    printCentered("ACCOUNT BALANCE");
    printEmptyLine();
    printBorder();

    snprintf(message, sizeof(message),
             "Available Balance: %.2f", account->balance);

    printf("\n        %s\n", message);

    waitForEnter();
}


void depositMoney(Account *account)
{
    float amount;

    clearScreen();

    printBorder();
    printEmptyLine();
    printCentered("DEPOSIT MONEY");
    printEmptyLine();
    printBorder();

    printf("\n        Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\n        Invalid amount!");

        waitForEnter();

        return;
    }

    account->balance += amount;

    printf("\n        Deposit Successful!");
    printf("\n        Amount Deposited: %.2f", amount);
    printf("\n        New Balance: %.2f", account->balance);

    waitForEnter();
}


void withdrawMoney(Account *account)
{
    float amount;

    clearScreen();

    printBorder();
    printEmptyLine();
    printCentered("WITHDRAW MONEY");
    printEmptyLine();
    printBorder();

    printf("\n        Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\n        Invalid amount!");

        waitForEnter();

        return;
    }

    if (amount > account->balance)
    {
        printf("\n        Insufficient Balance!");

        waitForEnter();

        return;
    }

    account->balance -= amount;

    printf("\n        Withdrawal Successful!");
    printf("\n        Amount Withdrawn: %.2f", amount);
    printf("\n        Remaining Balance: %.2f", account->balance);

    waitForEnter();
}


void displayMenu()
{
    printBorder();
    printEmptyLine();
    printCentered("C ATM SIMULATOR");
    printEmptyLine();
    printCentered("1. Check Balance ");
    printCentered("2. Deposit Money ");
    printCentered("3. Withdraw Money");
    printCentered("4. Exit          ");
    printEmptyLine();
    printBorder();
}


// ==================== MAIN FUNCTION ====================

int main()
{
    Account account = {
        1001,
        1234,
        5000.00
    };

    int choice;

    // First screen
    clearScreen();

    // Login
    if (!authenticateUser(&account))
    {
        return 0;
    }


    // ATM Menu
    while (1)
    {
        clearScreen();

        displayMenu();

        printf("\n        Enter your choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                checkBalance(&account);
                break;

            case 2:
                depositMoney(&account);
                break;

            case 3:
                withdrawMoney(&account);
                break;

            case 4:
                clearScreen();

                printBorder();
                printEmptyLine();
                printCentered("THANK YOU!");
                printEmptyLine();
                printCentered("Please Visit Again");
                printEmptyLine();
                printBorder();

                return 0;

            default:
                printf("\n        Invalid choice!");

                waitForEnter();
        }
    }

    return 0;
}