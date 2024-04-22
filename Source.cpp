#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#define TAXRATE 0.25

FILE* fp;
FILE* txtp;

void title();
void addEmployee();
void payroll();
void employeeManagement();
void viewEmployees();
void editEmployee();
void removeEmployee();
void loginScreen();

void main() {
	loginScreen();
}

void title() {
	system("cls");
	int selectionNum = 0;

	cout << "INSTAFORM\n\n1. Payroll\n2. Employee Management\n3. Exit\nSelect Option: ";
	cin >> selectionNum;

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
}

void payroll() {
	system("cls");
	fp = fopen("employeeTable.txt", "r");
	txtp = fopen("employerPayStub.txt", "a");

	string date, currentEmployeeFirstName, currentEmployeeLastName;
	int currentEmployeeId;
	double currentEmployeePayrate, grossToEmployee, netToEmployee, amtTaxed, totalPaidOvr, hoursWorked, totalPaidToEmployees, totalPaidToTaxes;
	totalPaidToTaxes = totalPaidToEmployees = 0.0;

	cout << "Enter Date of Payroll: ";
	cin >> date;

	fprintf(txtp, "Payroll for %s\n\n%4s  %8s %17s %16s %20s %17s %16s %21s\n", date.c_str(), "ID", "First Name", "Last Name", "Pay Rate", "Hours Worked", "Gross Pay", "Net Pay", "Amount Taxed");
	//prints header with category names

		while (!feof(fp)) {
			fscanf(fp, "%d %s %s %lf\n", &currentEmployeeId, &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
			printf("Enter Hours worked for %s %s: ", currentEmployeeFirstName, currentEmployeeLastName);
			cin >> hoursWorked;

			grossToEmployee = currentEmployeePayrate * hoursWorked;
			netToEmployee = grossToEmployee - (grossToEmployee * TAXRATE);
			amtTaxed = grossToEmployee - netToEmployee;
			totalPaidToEmployees += netToEmployee;
			totalPaidToTaxes += amtTaxed;

			fprintf(txtp, "%4d %11s %17s %16.2lf %20.2lf %17.2lf %16.2lf %21.2lf\n",currentEmployeeId, currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate, hoursWorked, grossToEmployee, netToEmployee, amtTaxed);
		}

		totalPaidOvr = totalPaidToEmployees + totalPaidToTaxes;
		fprintf(txtp, "\nTotal to pay to Employees: %.2lf\nTotal Paid to taxes: %.2lf\nOverall Total to pay: %.2lf\n\n", totalPaidToEmployees, totalPaidToTaxes, totalPaidOvr);
		printf("\nTotal to pay to Employees: %.2lf\nTotal Paid to taxes: %.2lf\nOverall Total to pay: %.2lf\n\n", totalPaidToEmployees, totalPaidToTaxes, totalPaidOvr);
		system("pause");
		fclose(fp);
		fclose(txtp);
		title();
}

void employeeManagement(){
	system("cls");
	int selectionNum;
	cout << "EMPLOYEE MANAGEMENT\n\n1. Add Employee\n2. View Employees\n3. Edit Employee\n4. Remove Employee\n5. Exit to title\nSelect Option: ";
	cin >> selectionNum;

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
}

void addEmployee() {
	system("cls");
	fp = fopen("employeeTable.txt", "a");
	txtp = fopen("employeeTable.txt", "r");
	char addEmployeeFirstName[25];
	char addEmployeeLastName[25];
	double addEmployeePayRate;
	int addEmployeeId;

	cout << "Enter employee full name: ";
	cin >> addEmployeeFirstName >> addEmployeeLastName;
	cout << "Enter employee pay rate: ";
	cin >> addEmployeePayRate;
	cout << "Enter a unique Id for this employee: ";
	cin >> addEmployeeId;

	fprintf(fp, "%d %s %s %.2lf\n", addEmployeeId, addEmployeeFirstName, addEmployeeLastName, addEmployeePayRate);

	fclose(txtp);
	fclose(fp);
	employeeManagement();
}

void viewEmployees() {
	system("cls");
	fp = fopen("employeeTable.txt", "r");
	string currentEmployeeFirstName, currentEmployeeLastName;
	double currentEmployeePayrate;
	int currentEmployeeId;
	printf("EMPLOYEE VIEW\n\n");
	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %lf\n", &currentEmployeeId, &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
		printf("ID: %d NAME: %s %s PAYRATE: $%.2lf/hour\n", currentEmployeeId, currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate);
	}
	fclose(fp);
	system("pause");
	employeeManagement();
}

void editEmployee() {
	int selectedId, savedId;
	char newFirstName[25], newLastName[25], savedFirstName[25], savedLastName[25];
	double newPayrate, savedPayrate;

	system("cls");
	fp = fopen("employeeTable.txt", "r");
	string currentEmployeeFirstName, currentEmployeeLastName;
	double currentEmployeePayrate;
	int currentEmployeeId;
	printf("EMPLOYEE VIEW\n\n");
	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %lf\n", &currentEmployeeId, &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
		printf("ID: %d NAME: %s %s PAYRATE: $%.2lf/hour\n", currentEmployeeId, currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate);
	}
	fclose(fp);

	cout << "Enter ID of employee you would like to edit: ";
	cin >> selectedId;
	system("cls");

	cout << "Enter New First Name: ";
	cin >> newFirstName;
	cout << "Enter New Last Name: ";
	cin >> newLastName;
	cout << "Enter New Payrate: ";
	cin >> newPayrate;

	fp = fopen("employeeTableClone.txt", "a");
	txtp = fopen("employeeTable.txt", "r");
	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		if (savedId == selectedId) {
			fprintf(fp, "%d %s %s %.2lf\n", selectedId, newFirstName, newLastName, newPayrate);
		}
		else {
			fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
		}
	}
	fclose(fp);
	fclose(txtp);

	fp = fopen("employeeTable.txt", "w");
	fprintf(fp, "");
	fclose(fp);

	fp = fopen("employeeTable.txt", "a");
	txtp = fopen("employeeTableClone.txt", "r");
	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
	}
	fclose(fp);
	fclose(txtp);
	
	fp = fopen("employeeTableClone.txt", "w");
	fprintf(fp, "");
	fclose(fp);
	employeeManagement();
}

void removeEmployee() {
	int selectedId, savedId;
	char newFirstName[25], newLastName[25], savedFirstName[25], savedLastName[25];
	double newPayrate, savedPayrate;

	system("cls");
	fp = fopen("employeeTable.txt", "r");
	string currentEmployeeFirstName, currentEmployeeLastName;
	double currentEmployeePayrate;
	int currentEmployeeId;
	printf("EMPLOYEE VIEW\n\n");
	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %lf\n", &currentEmployeeId, &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
		printf("ID: %d NAME: %s %s PAYRATE: $%.2lf/hour\n", currentEmployeeId, currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate);
	}
	fclose(fp);

	cout << "Enter ID of employee you would like to remove: ";
	cin >> selectedId;
	system("cls");

	fp = fopen("employeeTableClone.txt", "a");
	txtp = fopen("employeeTable.txt", "r");
	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		if (savedId != selectedId) {
			fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
		}
	}
	fclose(fp);
	fclose(txtp);

	fp = fopen("employeeTable.txt", "w");
	fprintf(fp, "");
	fclose(fp);

	fp = fopen("employeeTable.txt", "a");
	txtp = fopen("employeeTableClone.txt", "r");
	while (!feof(txtp)) {
		fscanf(txtp, "%d %s %s %lf\n", &savedId, &savedFirstName, &savedLastName, &savedPayrate);
		fprintf(fp, "%d %s %s %.2lf\n", savedId, savedFirstName, savedLastName, savedPayrate);
	}
	fclose(fp);
	fclose(txtp);

	fp = fopen("employeeTableClone.txt", "w");
	fprintf(fp, "");
	fclose(fp);
	employeeManagement();
}

void loginScreen() {
	system("cls");
	char enteredUsername[25], enteredPassword[25], validUsername[25], validPassword[25];
	int appStarted;

	txtp = fopen("LoginInfo.txt", "r");
	fscanf(txtp, "%d %s %s", &appStarted, &validUsername, &validPassword);
	fclose(txtp);

	if(appStarted != 1){
		cout << "Create Username: ";
		cin >> enteredUsername;
		cout << "Create Password: ";
		cin >> enteredPassword;

		fp = fopen("LoginInfo.txt", "w");
		fprintf(fp, "%d %s %s", 1, enteredUsername, enteredPassword);
		fclose(fp);
		cout << "You will now enter your first employee...\n";
		system("pause");
		addEmployee();
	}
	else {
		cout << "Enter Username: ";
		cin >> enteredUsername;
		cout << "Enter Password: ";
		cin >> enteredPassword;

		if (strcmp(enteredUsername, validUsername) + strcmp(enteredPassword, validPassword) == 0) {
			title();
		}
		else {
			printf("Invalid Username or Password\n");
			system("pause");
			loginScreen();
		}
	}
}
