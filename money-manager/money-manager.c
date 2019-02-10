/*
==============================================================================
Author	: Tifan Dwi Avianto (github.com/ifananvity)
Version	: 1.0 - 11/12/2017
Desc	: Money manager. Calculates income and expenses for x(user input) days
==============================================================================
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>

// Declaration
char menuSelection;
char trxSelection;
int balance;
int askDays, askTrx;
int trx, totalTrx, total;
int income[10], incomeSource[10];
int expense[10];
int flag, flag2;
int k = 0;
int l = 0;
int i, j, o, p;     // loop vars

// Constants definitions
#define TRUE 1
#define FALSE 0

// Function prototypes
void printTitle(void);
void promptInitialLaunch(void);
void mainMenu(void);
void transactionMenu(void);
void incomeTransaction(void);
void expenseTransaction(void);
void printStats(void);

int main(void) {
	printTitle();
	promptInitialLaunch();
	mainMenu();
	
	return EXIT_SUCCESS;
}

/* ------------------------------ FUNCTIONS ------------------------------ */

void printTitle() {
	printf("               Money McMoneyface\n");
	printf("     \"Budget, finance and expense tracker.\"\n\n");
}

void promptInitialLaunch() {
	printf("Welcome! First off, add your current balance.\n");

	// ask for current balance
	printf("Current balance: ");
	scanf("%d", &balance);
}

void mainMenu() {
	flag = FALSE;
	while (!flag) {
		printf("\n-------- MENU --------\n");
		printf("Balance: Rp.%d\n", balance);
		printf("1. Transaction\n");
		printf("2. Stats\n");
		printf("0. Exit\n");
		fflush(stdin);
		menuSelection = getchar();

		switch (menuSelection) {
			case '1' : {
				transactionMenu();
				break;
			}
			case '2' : {
				printStats();
				break;
			}
			case '0' : {
				flag = TRUE;
				break;
			}
			default: {
				printf("Invalid input\n");
			}
		}
	}
}

void transactionMenu() {
	flag2 = FALSE;
	while (!flag2) {
		printf("\n-------- Transaction --------\n");
		printf("1. Income\n");
		printf("2. Expense\n");
		printf("0. < Menu\n");
		fflush(stdin);
		trxSelection = getchar();

		switch (trxSelection) {
			case '1' : {
				incomeTransaction();
				flag2 = TRUE;
				break;
			}
			case '2' : {
				expenseTransaction();
				flag2 = TRUE;
				break;
			}
			case '0' : {
				flag2 = TRUE;
				break;
			}
			default : {
				printf("Invalid input\n");
			}
		}
	}
}

void incomeTransaction() {
	printf("\n-------- Income --------\n");
	printf("1. Allowance\n");
	printf("2. Salary\n");
	printf("3. Petty cash\n");
	printf("4. Bonus\n");
	printf("5. Other\n");
	scanf("%d", &incomeSource[k]);

	printf("Amount: ");
	scanf("%d", &income[k]);

	// add income to balance
	balance += income[k];

	// increment
	k++;
}

void expenseTransaction() {
	printf("\n-------- Expense --------\n");
	printf("How many days would you want to input your expenses? ");
	scanf("%d", &askDays);

	for (i = 1; i <= askDays; i++) {
		// set initial value
		totalTrx = 0;
		
		printf("Day %d\n", i);
		printf("  How many transaction? ");
		scanf("%d", &askTrx);
		for (j = 1; j <= askTrx; j++) {
			if (j == 1) {
				printf("    1st transaction: ");
			} else if (j == 2) {
				printf("    2nd transaction: ");
			} else if (j == 3) {
				printf("    3rd transaction: ");
			} else {
				printf("    %dth transaction: ", j);
			}
			scanf("%d", &trx);

			totalTrx += trx;
		}
		printf("  Expenses on day %d is Rp.%d\n", i, totalTrx);

		expense[l] = totalTrx;
		total += totalTrx;

		// subtract balance from expenses
		balance -= total;

		// increment
		l++;
	}
	printf("Total expenditure: Rp.%d\n", total);
}

void printStats() {
	printf("\n-------- Stats --------\n");
	if (income[0] == 0 && expense[0] == 0) {
		printf("No data available.\n");
	} else {
		printf("Balance: Rp.%d\n", balance);

		// income history
		printf("-Incomes\n");
		for (o = 0; o < k; o++) {
			printf(" %d ", income[o]);
			switch (incomeSource[o]) {
				case 1 : {
					printf("(Allowance)\n");
					break;
				}
				case 2 : {
					printf("(Salary)\n");
					break;
				}
				case 3 : {
					printf("(Petty cash)\n");
					break;
				}
				case 4 : {
					printf("(Bonus)\n");
					break;
				}
				case 5 : {
					printf("(Other)\n");
					break;
				}
				default : {
					printf("(Null)\n");
				}
			}
		}

		// expenses history
		printf("-Expenses\n");
		for (p = 0; p < l; p++) {
			printf(" %d\n", expense[p]);
		}
	}
}