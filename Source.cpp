#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
//defines no warnings, adds needed header files, and uses std namespace

#define TAXRATE 0.25
//defines constant taxrate

FILE* fp;
FILE* txtp;
//declares FILE pointers

int firstStartup = 0;

void decrypt(char*);
void encrypt(char*);
void title();
void addEmployee();
void payroll();
void employeeManagement();
void viewEmployees();
void editEmployee();
void removeEmployee();
void loginScreen();
//function prototypes

void main() {
	loginScreen();
}
//main starts at loginScreen

void title() {
	system("cls");
	int selectionNum = 0;
	//clears screen and delcares selectionNum

	cout << "INSTAFORM\n\n1. Payroll\n2. Employee Management\n3. Exit\nSelect Option: ";
	cin >> selectionNum;
	//prommpts selection

	switch (selectionNum) {
		case 1:
			payroll();
			break;
		case 2:
			employeeManagement();
			break;
		case 3:
			break;
		default:
			title();
			break;
	}
	//switch case for user selection redirection
}
//displays title

void payroll() {
	system("cls");
	fp = fopen("employeeTable.txt", "r");
	txtp = fopen("employerPayStub.txt", "a");
	//clears screen, and opens files for input/output

	char date[10], currentEmployeeFirstName[25], currentEmployeeLastName[25];
	int currentEmployeeId;
	double currentEmployeePayrate, grossToEmployee, netToEmployee, amtTaxed, totalPaidOvr, hoursWorked, totalPaidToEmployees, totalPaidToTaxes;
	totalPaidToTaxes = totalPaidToEmployees = 0.0;
	//declares and initializes needed variables

	cout << "Enter Date of Payroll: ";
	cin >> date;
	//input prompt for date

	fprintf(txtp, "Payroll for %s\n\n%4s  %8s %17s %16s %20s %17s %16s %21s\n", date, "ID", "First Name", "Last Name", "Pay Rate", "Hours Worked", "Gross Pay", "Net Pay", "Amount Taxed");
	//prints header with category names

		while (!feof(fp)) {
			fscanf(fp, "%d %s %s %lf\n", &currentEmployeeId, &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
			decrypt(currentEmployeeFirstName);
			decrypt(currentEmployeeLastName);
			//scans employeeTable and decrypts names

			printf("Enter Hours worked for %s %s: ", currentEmployeeFirstName, currentEmployeeLastName);
			cin >> hoursWorked;
			//input prompt for hours worked for given employee

			grossToEmployee = currentEmployeePayrate * hoursWorked;
			netToEmployee = grossToEmployee - (grossToEmployee * TAXRATE);
			amtTaxed = grossToEmployee - netToEmployee;
			totalPaidToEmployees += netToEmployee;
			totalPaidToTaxes += amtTaxed;
			//calculates gross pay, net pay, and amount taken from tax and adds to total paid to employees and taxes

			fprintf(txtp, "%4d %11s %17s %16.2lf %20.2lf %17.2lf %16.2lf %21.2lf\n",currentEmployeeId, currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate, hoursWorked, grossToEmployee, netToEmployee, amtTaxed);
			//prints line of employee info
		}
		//while the file is not at end of file it will run through this loop

		totalPaidOvr = totalPaidToEmployees + totalPaidToTaxes;
		//calculates overall paid from employer

		fprintf(txtp, "\nTotal to pay to Employees: %.2lf\nTotal Paid to taxes: %.2lf\nOverall Total to pay: %.2lf\n\n", totalPaidToEmployees, totalPaidToTaxes, totalPaidOvr);
		printf("\nTotal to pay to Employees: %.2lf\nTotal Paid to taxes: %.2lf\nOverall Total to pay: %.2lf\n\n", totalPaidToEmployees, totalPaidToTaxes, totalPaidOvr);
		//prints footer to screen and file

		system("pause");
		fclose(fp);
		fclose(txtp);
		title();
		//pauses screen until keypress, closes the FILE pointers, and sends user to title
}
//function to take in hours worked output payroll to employerPayStub.txt

void employeeManagement(){
	system("cls");
	int selectionNum;
	//clears screen and declares selectionNum

	cout << "EMPLOYEE MANAGEMENT\n\n1. Add Employee\n2. View Employees\n3. Edit Employee\n4. Remove Employee\n5. Exit to title\nSelect Option: ";
	cin >> selectionNum;
	//input prompt for selectionNum

	switch (selectionNum) {
		case 1:
			addEmployee();
			break;
		case 2:
			viewEmployees();
			break;
		case 3:
			editEmployee();
			break;
		case 4:
			removeEmployee();
			break;
		case 5:
			title();
			break;
		default:
			employeeManagement();
			break;
	}
	//switch case for selection and redirection
}
//displays employee management options

void addEmployee() {
	system("cls");
	fp = fopen("employeeTable.txt", "a");
	txtp = fopen("employeeTable.txt", "r");
	//clears screen and initializes FILE pointers

	char addEmployeeFirstName[25], addEmployeeLastName[25];
	double addEmployeePayRate;
	int addEmployeeId;
	//declares needed variables

	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &addEmployeeId, &addEmployeeFirstName, &addEmployeeLastName, &addEmployeePayRate);
	}

	cout << "Enter employee full name: ";
	cin >> addEmployeeFirstName >> addEmployeeLastName;
	cout << "Enter employee pay rate: ";
	cin >> addEmployeePayRate;
	//input prompt for employees name, and payrate

	encrypt(addEmployeeFirstName);
	encrypt(addEmployeeLastName);
	//encrypts name

	if (firstStartup != 0) {
		addEmployeeId = 1;
		firstStartup = 0;
		fprintf(fp, "%d %s %s %.2lf\n", addEmployeeId, addEmployeeFirstName, addEmployeeLastName, addEmployeePayRate);
		fclose(txtp);
		fclose(fp);
		employeeManagement();
	}
	//creates unique id for added employee

	fprintf(fp, "%d %s %s %.2lf\n", addEmployeeId + 1, addEmployeeFirstName, addEmployeeLastName, addEmployeePayRate);
	//prints employee information to employeeTable.txt

	fclose(txtp);
	fclose(fp);
	employeeManagement();
	//closes FILE pointers and redirects to employee management
}
//takes input for employee info and prints it to employee table

void viewEmployees() {
	system("cls");
	fp = fopen("employeeTable.txt", "r");
	//clears screen and opens declares fp to read "employeeTable.txt"

	char currentEmployeeFirstName[25], currentEmployeeLastName[25];
	double currentEmployeePayrate;
	int currentEmployeeId;
	//declares needed variable

	printf("EMPLOYEE VIEW\n\n");

	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %lf\n", &currentEmployeeId, &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
		decrypt(currentEmployeeFirstName);
		decrypt(currentEmployeeLastName);
		printf("ID: %d NAME: %s %s PAYRATE: $%.2lf/hour\n", currentEmployeeId, currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate);
	}//While the program hasn't scanned end of file character it will scan a line of employee data, decrypt it, and print it to screen
	
	fclose(fp);
	system("pause");
	employeeManagement();
	//closes fp, pauses screen until key press, and redirects to employee management screen
}
//scans employeeTable and displays data to screen

void editEmployee() {
	int selectedId, savedId;
	char newFirstName[25], newLastName[25], savedFirstName[25], savedLastName[25];
	double newPayrate, savedPayrate;
	//declares needed variables

	system("cls");
	fp = fopen("employeeTable.txt", "r");
	//clears screen and opens fp to read employeeTable.txt

	printf("EMPLOYEE VIEW\n\n");

	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		decrypt(savedFirstName);
		decrypt(savedLastName);
		printf("ID: %d NAME: %s %s PAYRATE: $%.2lf/hour\n", savedId, savedFirstName, savedLastName, savedPayrate);
		//scans employee data from employee table, decrypts data, prints data to screen
	}//while the end of file character is not reached, this code will loop

	fclose(fp);

	cout << "Enter ID of employee you would like to edit: ";
	cin >> selectedId;
	system("cls");
	//prompts for Id of employee to edit

	cout << "Enter New First Name: ";
	cin >> newFirstName;
	cout << "Enter New Last Name: ";
	cin >> newLastName;
	cout << "Enter New Payrate: ";
	cin >> newPayrate;
	encrypt(newFirstName);
	encrypt(newLastName);
	//prompts for new employee data and encrypts

	fp = fopen("employeeTableClone.txt", "a");
	txtp = fopen("employeeTable.txt", "r");
	//opens input and output FILE pointers

	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		if (savedId == selectedId) {
			fprintf(fp, "%d %s %s %.2lf\n", selectedId, newFirstName, newLastName, newPayrate);
		}
		else {
			fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
		}
		//scans and saves employee data from current line, if the selected ID matches the scanned id it will print new info else it prints saved data to clone file
	}

	fclose(fp);
	fclose(txtp);
	//closes FILE pointers

	fp = fopen("employeeTable.txt", "w");
	fprintf(fp, "");
	fclose(fp);
	//removes data from original employeeTable

	fp = fopen("employeeTable.txt", "a");
	txtp = fopen("employeeTableClone.txt", "r");
	//opens input and output FILE pointers

	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
	}//while end of file is not scanned it will scan data from clone table and prints to original table

	fclose(fp);
	fclose(txtp);
	//closes FILE pointers
	
	fp = fopen("employeeTableClone.txt", "w");
	fprintf(fp, "");
	fclose(fp);
	employeeManagement();
	//removes data from clone table and redirects to employeeManagement screen
}
//edits employee info

void removeEmployee() {
	int selectedId, savedId;
	char newFirstName[25], newLastName[25], savedFirstName[25], savedLastName[25];
	double newPayrate, savedPayrate;
	//declares needed variables

	system("cls");
	fp = fopen("employeeTable.txt", "r");
	printf("EMPLOYEE VIEW\n\n");
	//clears screen, opens FILE pointer, prints header

	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		decrypt(savedFirstName);
		decrypt(savedLastName);
		printf("ID: %d NAME: %s %s PAYRATE: $%.2lf/hour\n", savedId, savedFirstName, savedLastName, savedPayrate);
		//scans employee data from file, decrypts it, prints it to screen
	}//While end of file character isn't scaneed it runs this loop
	fclose(fp);

	cout << "Enter ID of employee you would like to remove: ";
	cin >> selectedId;
	system("cls");
	//prompts input for ID of desired employee to remobe and clears screen

	fp = fopen("employeeTableClone.txt", "a");
	txtp = fopen("employeeTable.txt", "r");
	//opens input and output files

	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		if (savedId != selectedId) {
			fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
		}
	}//While eof isnt scaneed it will scan a line of employee data and if it doesn't match the desired employee it will print to clone table
	fclose(fp);
	fclose(txtp);
	//closes file pointers

	fp = fopen("employeeTable.txt", "w");
	fprintf(fp, "");
	fclose(fp);
	//removes data from original table

	fp = fopen("employeeTable.txt", "a");
	txtp = fopen("employeeTableClone.txt", "r");
	//opens input and output  FILE pointers

	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
	}//while eof inst scanned it will copy clone table to original
	fclose(fp);
	fclose(txtp);
	//closes file pointers

	fp = fopen("employeeTableClone.txt", "w");
	fprintf(fp, "");
	fclose(fp);
	employeeManagement();
	//removes data from clone table and redirects to employee management screen
}
//removes employee info

void loginScreen() {
	system("cls");
	char enteredUsername[25], enteredPassword[25], validUsername[25], validPassword[25];
	int appStarted;
	//clears screen and declares needed variables

	txtp = fopen("LoginInfo.txt", "r");
	fscanf(txtp, "%d %s %s", &appStarted, &validUsername, &validPassword);
	decrypt(validUsername);
	decrypt(validPassword);
	fclose(txtp);
	//scans and decrypts valid login info

	if(appStarted != 1){
		cout << "Create Username: ";
		cin >> enteredUsername;
		cout << "Create Password: ";
		cin >> enteredPassword;
		//prompts creation of login info

		fp = fopen("LoginInfo.txt", "w");
		encrypt(enteredUsername);
		encrypt(enteredPassword);
		fprintf(fp, "%d %s %s", 1, enteredUsername, enteredPassword);
		fclose(fp);
		//encrypts and prints info to File

		cout << "You will now enter your first employee...\n";
		system("pause");
		firstStartup = 1;
		addEmployee();
		//redirects user to create first employee
	}//if previous app startup is not detected, account creation is prompted
	else {
		cout << "Enter Username: ";
		cin >> enteredUsername;
		cout << "Enter Password: ";
		cin >> enteredPassword;
		//prompts user input for login info

		if (strcmp(enteredUsername, validUsername) + strcmp(enteredPassword, validPassword) == 0) {
			title();
		}
		else {
			printf("Invalid Username or Password\n");
			system("pause");
			loginScreen();
		}//if the input info matches the valid login info it will redirect to title, else Invalif info message is displayed
	}
}
//prompts login and startup sequence

void encrypt(char* data) {
	char c;
	for (int i = 0; i <= strlen(data) - 1; i++) {
		data[i] += '2' + (i * i);
	}
}
//encrypts string

void decrypt(char* data) {
	for (int i = 0; i <= strlen(data) - 1; i++) {
		data[i] -= '2' + (i * i);
	}
}
//decrypts string
