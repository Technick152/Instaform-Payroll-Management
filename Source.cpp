#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
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

void main() {
	title();
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

	string date;
	string currentEmployeeFirstName, currentEmployeeLastName;
	double currentEmployeePayrate, grossToEmployee, netToEmployee, amtTaxed, totalPaidOvr, hoursWorked, totalPaidToEmployees, totalPaidToTaxes;
	totalPaidToTaxes = totalPaidToEmployees = 0.0;

	cout << "Enter Date of Payroll: ";
	cin >> date;

	fprintf(txtp, "Payroll for %s\n\n%8s %17s %16s %20s %17s %16s %21s\n", date.c_str(), "First Name", "Last Name", "Pay Rate", "Hours Worked", "Gross Pay", "Net Pay", "Amount Taxed");
	//prints header with category names

		while (!feof(fp)) {
			fscanf(fp, "%s %s %lf\n", &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
			printf("Enter Hours worked for %s, %s: ", currentEmployeeFirstName, currentEmployeeLastName);
			scanf("%lf", &hoursWorked);

			grossToEmployee = currentEmployeePayrate * hoursWorked;
			netToEmployee = grossToEmployee - (grossToEmployee * TAXRATE);
			amtTaxed = grossToEmployee - netToEmployee;
			totalPaidToEmployees += netToEmployee;
			totalPaidToTaxes += amtTaxed;
			//

			fprintf(txtp, "%10s %17s %16.2lf %20.2lf %17.2lf %16.2lf %21.2lf\n", currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate, hoursWorked, grossToEmployee, netToEmployee, amtTaxed);
		}

		totalPaidOvr = totalPaidToEmployees + totalPaidToTaxes;
		fprintf(txtp, "\nTotal to pay to Employees: %.2lf\nTotal Paid to taxes: %.2lf\nOverall Total to pay: %.2lf\n\n", totalPaidToEmployees, totalPaidToTaxes, totalPaidOvr);
		fclose(fp);
		fclose(txtp);
		title();
}

void employeeManagement() {
	system("cls");
	int selectionNum;
	cout << "EMPLOYEE MANAGEMENT\n\n1. Add Employee\n2. View Employees\n3. Exit to Title\nSelect Option: ";
	cin >> selectionNum;

	switch (selectionNum) {
		case 1:
			addEmployee();
			break;
		case 2:
			viewEmployees();
			break;
		case 3:
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
	char addEmployeeFirstName[25];
	char addEmployeeLastName[25];
	double addEmployeePayRate;

	cout << "Enter employee full name: ";
	cin >> addEmployeeFirstName >> addEmployeeLastName;
	cout << "Enter employee pay rate: ";
	cin >> addEmployeePayRate;

	fprintf(fp, "\n%s %s %.2lf", addEmployeeFirstName, addEmployeeLastName, addEmployeePayRate);

	fclose(fp);
	title();
}

void viewEmployees() {
	system("cls");
	fp = fopen("employeeTable.txt", "r");
	string currentEmployeeFirstName, currentEmployeeLastName;
	double currentEmployeePayrate;
	printf("EMPLOYEE VIEW\n\n");
	while (!feof(fp)) {
		fscanf(fp, "%s %s %lf\n", &currentEmployeeFirstName, &currentEmployeeLastName, &currentEmployeePayrate);
		printf("%s, %s, $%.2lf/hour\n", currentEmployeeFirstName, currentEmployeeLastName, currentEmployeePayrate);
	}
	system("pause");
	fclose(fp);
	employeeManagement();
}
