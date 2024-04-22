# PayrollManagement

   This is a very early prototype to a business management application I would like to build.
I'm going to first go over how to use this version of the app then go over how I would like to improve and scale.

USE:

    Upon startup you will be promted to create a username and password then,you will be prompted to write the full name of the employee which is "First Last" format,
next you will enter the Pay rate per hour. When you have your employees saved go back to the title and select the "Payroll" option where you will be prompted for the hours worked
for each employee, this will be saved to "employerPayStub.txt" where you can see the breakdown of the gross pay, net pay, and amount taken out in taxes for each employee.
There will be a footer showing the total paid to the employees, total paid to taxes, and Overall total paid.

Update Plan 1: Data security

      Right now the employee data, and login info are in unguarded text files, in order to protect this information for now I plan on hashing and dehashing
the data so that viewing the employee data and login info is unrecognizeable without the dehashing key

Update Plan 2: UI

    This one is pretty easy, I am already working on a port to C#.net framework which I have used in the past, but until I do that the console will do, although
I could just port to a standard web frontend design which I'm less experienced in but often scales better.

Update Plan 3: Database

      Currently the data storage system is reading and writing from a txt file, this is good for now because I dont plan on my app being used commercially, with that being said I would like to practice my ability to create real, scaleable full stack apps so I will need a real data solution. I have used mongoDB in a previous project so that is my number 1 consideration for now, but I would also like to explore SQL options like SQLite and MySQL
