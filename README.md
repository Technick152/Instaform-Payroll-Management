# PayrollManagement

   This is a very early prototype to a business management application I would like to build.
I'm going to first go over how to use this version of the app then go over how I would like to improve and scale.

USE:
    You will first need to add employees which will be under the "Employee managment" option on the tile screen, then select "Add Employee",
you will be prompted to write the full name of the employee which is "First Last" format, next you will enter the Pay rate per hour.
When you have your employees saved go back to the title and select the "Payroll" option where you will be prompted for the hours worked
for each employee, this will be saved to "employerPayStub.txt" where you can see the breakdown of the gross pay, net pay, and amount taken out in taxes for each employee.
There will be a footer showing the total paid to the employees, total paid to taxes, and Overall total paid.
For now to edit or remove employees you must navigate to the project file "employeeTable.txt" and manually remove or edit the info

ISSUE 1: Removal and Editing of employees/employee information
    This is hard to do efficiently in the current .txt file format I am using, the obvious solution is to integrate a real data base using SQL or other database like MongoDB.
I have experimented with SQLite in a previous project but my program was very buggy with the implementation, and I would often corrupt the DB file, until I learn
how to integrate that my current plan is to just write to a new txt file with the information changed then overwrite "employeeTable.txt" with the new information

ISSUE 2: UI
    This one is pretty easy, I am already working on a port to C#.net framework which I have used in the past, but until I do that the console will do, although
I could just port to a standard web frontend design which I'm less experienced in but often scales better.
