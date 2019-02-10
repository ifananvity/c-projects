/*
==============================================================================
Author	: Tifan Dwi Avianto (github.com/ifananvity)
Version	: 1.0 - 12/12/2017
Desc	: Assess fees on tollway depending on vehicle type and calculate total
          income 
==============================================================================
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Declaration
int car, bus, truck;
char username[10];
char password[256] = {0}, c;
int pos;
int flag;
int counter;

// Constants definitions
#define CAR_FEE 2000
#define BUS_FEE 3000
#define TRUCK_FEE 5000
#define TRUE 1;
#define FALSE 0;

// Function prototypes
void inputPassword(void);
void mainMenu(void);
int inputAmount(void);
void summary(void);
void exitMainMenu(void);

int main(void) {
	// set initial value
	counter = 2;

	while (counter >= 0) {
		// prompt for username and password
		printf("Username= ");
		scanf("%s", username);
		printf("Password= ");
		inputPassword();

		// validate username and password
		if (!strcmp(username, "admin") && !strcmp(password, "admin")) {
			mainMenu();
		} else {
			printf("Wrong username or password. Try again. %d attempt left\n\n", counter);

			// decrement counter
			counter--;
		}
	}
	
	return EXIT_SUCCESS;
}

/* ------------------------------ FUNCTIONS ------------------------------ */

void mainMenu() {
	flag = FALSE;
	while (!flag) {
		printf("\n---------- MENU ----------\n");
		printf("Add vehicles:\n");
		printf("1. Car			4. Summary\n");
		printf("2. Bus			0. Exit\n");
		printf("3. Truck\n");
		fflush (stdin);
		char selection = getchar();

		switch (selection) {
			case '1' : {
				car += inputAmount();
				break;
			}
			case '2' : {
				bus += inputAmount();
				break;
			}
			case '3' : {
				truck += inputAmount();
				break;
			}
			case '4' : {
				summary();
				break;
			}
			case '0' : {
				exitMainMenu();
				break;
			}
			default : {
				printf("Invalid input\n");
			}
		}

		// reset counter
		counter = 2;
	}
}

void inputPassword() {
	// Change password input to asterisk "*" (hides it)
	pos = 0;
	do {
    	c = getch();

    	if(isprint(c)) {
        	password[pos++] = c;
        	printf("%c", '*');
    	}
    	else if(c == '\b' && pos) {
        	password[pos--] = '\0';
        	printf("%s", "\b \b");
    	}
	} while(c != '\r');

	printf("\n");
}

int inputAmount() {
	int temp;

	// ask the amount of vehicle has entered
	printf("Amount: ");
	scanf("%d", &temp);
	return temp;
}

void summary() {
	printf("\n-------- Summary --------\n");
	if (car == 0 && bus == 0 && truck == 0) {
		printf("No data available.\n");
	} else {
		printf("Car   : %d\n", car);
		printf("Bus   : %d\n", bus);
		printf("Truck : %d\n", truck);
		printf("Total : Rp.%d,-\n", car * CAR_FEE + bus * BUS_FEE + truck * TRUCK_FEE);
		
	}
	printf("Press any key to continue . . ."); getch();printf("\n");
}

void exitMainMenu() {
	printf("Warning: Data will be lost. Continue? (y/n) ");
	fflush(stdin);
	char warning = getchar();
	printf("\n");

	if (warning == 'y') {
		// reset
		car = bus = truck = 0;

		flag = TRUE;
	}
}
