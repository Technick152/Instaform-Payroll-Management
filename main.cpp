#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
//defines no warnings, adds needed header files, and uses std namespace

#define TAXRATE 0.25
//defines constant taxrate

FILE* fp;
FILE* txtp;
//declares FILE pointers

int firstStartup = 0;

class Employee {
public:
	int id = 0;
	char firstName[25] = "";
	char lastName[25] = "";
	double payRate = 0;
	double hoursWorked = 0;
	double lastHoursWorked = 0;
	double lastPaystub = 0;
	double totalPay = 0;
	double totalHours = 0;
};
//defines Employee class
Employee nullEmployee;
Employee employeeList[99];
int employeeNum = 0;
//defines nullEmployee, the Employee List and num of employees

void title();
void addEmployee();
void payroll();
void employeeManagement();
void viewEmployees();
void editEmployee();
void removeEmployee();
void loginScreen();
void changeLoginInfo();
void employeeVue();
void scanTable();
void printTableToScreen();
void saveTable(int);
void clearTable();
//function prototypes

void main() {
	scanTable();
	loginScreen();
}
//main starts at loginScreen

void title() {
	system("cls");
	int selectionNum = 0;
	//clears screen and delcares selectionNum

	cout << "INSTAFORM\n\n0. Change Login Info\n1. Payroll\n2. Employee Management\n3. Log Out\nSelect Option: ";
	cin >> selectionNum;
	//prommpts selection

	switch (selectionNum) {
		case 0:
			changeLoginInfo();
			break;
		case 1:
			payroll();
			break;
		case 2:
			employeeManagement();
			break;
		case 3:
			loginScreen();
			break;
		case 4:
			scanTable();
			printTableToScreen();
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

	char date[10];
	int index = 0;
	double grossToEmployee, netToEmployee, amtTaxed, totalPaidOvr, hoursWorked, totalPaidToEmployees, totalPaidToTaxes;
	totalPaidToTaxes = totalPaidToEmployees = 0.0;
	//declares and initializes needed variables

	cout << "Enter Date of Payroll: ";
	cin >> date;
	//input prompt for date

	fprintf(txtp, "Payroll for %s\n\n%4s  %8s %17s %16s %20s %17s %16s %21s\n", date, "ID", "First Name", "Last Name", "Pay Rate", "Hours Worked", "Gross Pay", "Net Pay", "Amount Taxed");
	//prints header with category names

		while (index < employeeNum) {
			printf("Enter Hours worked for %s %s: ", employeeList[index].firstName, employeeList[index].lastName);
			cin >> hoursWorked;
			//input prompt for hours worked for given employee

			grossToEmployee = employeeList[index].payRate * hoursWorked;
			netToEmployee = grossToEmployee - (grossToEmployee * TAXRATE);
			amtTaxed = grossToEmployee - netToEmployee;
			totalPaidToEmployees += netToEmployee;
			totalPaidToTaxes += amtTaxed;
			//calculates gross pay, net pay, and amount taken from tax and adds to total paid to employees and taxes

			fprintf(txtp, "%4d %11s %17s %16.2lf %20.2lf %17.2lf %16.2lf %21.2lf\n", employeeList[index].id, employeeList[index].firstName, employeeList[index].lastName, employeeList[index].payRate, hoursWorked, grossToEmployee, netToEmployee, amtTaxed);
			//prints line of employee info
			index++;
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
	if (firstStartup == 1) {
		employeeNum--;
		employeeList[employeeNum].id = 1;
		firstStartup = 0;
	}
	else {
		employeeList[employeeNum].id = employeeList[employeeNum - 1].id + 1;
	}

	cout << "Enter Employee First Name: ";
	cin >> employeeList[employeeNum].firstName;
	cout << "Enter Employee Last Name: ";
	cin >> employeeList[employeeNum].lastName;
	cout << "Enter Employee Pay Rate: ";
	cin >> employeeList[employeeNum].payRate;

	employeeNum++;
	saveTable(99);

	employeeManagement();
}
//takes input for employee info and prints it to employee table

void viewEmployees() {
	system("cls");
	printf("EMPLOYEE VIEW\n\n");
	printTableToScreen();
	system("pause");
	employeeManagement();
}
//scans employeeTable and displays data to screen

void editEmployee() {
	int selectedId, i = 0;
	char newFirstName[25], newLastName[25];
	double newPayrate;
	//declares needed variable

	system("cls");
	printf("EMPLOYEE VIEW\n\n");

	printTableToScreen();

	cout << "Enter ID of employee you would like to edit: ";
	cin >> selectedId;
	system("cls");
	//prompts for Id of employee to edit

	while (employeeList[i].id != selectedId) {i++;}

	cout << "Enter New First Name: ";
	cin >> employeeList[i].firstName;
	cout << "Enter New Last Name: ";
	cin >> employeeList[i].lastName;
	cout << "Enter New Payrate: ";
	cin >> employeeList[i].payRate;
	//prompts for new employee data

	saveTable(NULL);
	employeeManagement();
}
//edits employee info

void removeEmployee() {
	int selectedId;
	//declares needed variable

	system("cls");
	printf("EMPLOYEE VIEW\n\n");
	//clears screen and prints header

	printTableToScreen();

	cout << "Enter ID of employee you would like to remove: ";
	cin >> selectedId;

	clearTable();
	saveTable(selectedId);
	scanTable();

	system("cls");
	employeeManagement();
	//prompts input for ID of desired employee to remobe and clears screen
}
//removes employee info

void loginScreen() {
	system("cls");
	char enteredUsername[25], enteredPassword[25], validUsername[25], validPassword[25];
	int appStarted;
	//clears screen and declares needed variables

	txtp = fopen("LoginInfo.txt", "r");
	fscanf(txtp, "%d %s %s", &appStarted, &validUsername, &validPassword);
	fclose(txtp);
	//scans and decrypts valid login info

	if(appStarted != 1){
		changeLoginInfo();

		cout << "You will now enter your first employee...\n";
		system("pause");
		firstStartup = 1;
		addEmployee();
		//redirects user to create first employee
	}//if previous app startup is not detected, account creation is prompted
	else {
		cout << "INSTAFORM\n\nEnter Username: ";
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

void changeLoginInfo() {
	system("cls");
	char newUsername[25], newPassword[25];
	
	cout << "Create Username: ";
	cin >> newUsername;
	cout << "Create Password: ";
	cin >> newPassword;
	//prompts creation of login info

	fp = fopen("LoginInfo.txt", "w");
	fprintf(fp, "%d %s %s", 1, newUsername, newPassword);
	fclose(fp);
	//encrypts and prints info to File
}
//changes login info

void scanTable() {
	fp = fopen("employeeTable.txt", "r");
	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %lf\n", &employeeList[i].id, &employeeList[i].firstName, &employeeList[i].lastName, &employeeList[i].payRate);
		i++;
	}
	employeeNum = i;
	fclose(fp);
}

void printTableToScreen() {
	printf("%-5s %-15s %-15s %-5s\n", "ID", "First Name", "Last Name", "Pay Rate");
	for (int i = 0; i < employeeNum; i++) {
		printf("%-5d %-15s %-15s %-5.2lf\n", employeeList[i].id, employeeList[i].firstName, employeeList[i].lastName, employeeList[i].payRate);
	}
}

void saveTable(int excludedId) {
	clearTable();
	fp = fopen("employeeTable.txt", "a");
	for (int i = 0; i < employeeNum; i++) {
		if (employeeList[i].id != excludedId) {
			fprintf(fp, "%d %s %s %.2lf\n", employeeList[i].id, employeeList[i].firstName, employeeList[i].lastName, employeeList[i].payRate);
		}
	}
	fclose(fp);
}

void clearTable() {
	fp = fopen("employeeTable.txt", "w");
	fprintf(fp, "");
	fclose(fp);
}
