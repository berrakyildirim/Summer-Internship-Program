# Internship Data Management System

## Description
This project manages and processes internship student data from a file. It allows users to search for student information, sort records by scores or letter grades, and view statistics about students in various departments.

The program processes data such as student names, surnames, department codes, semesters, scores, and letter grades (calculated based on the scores). It supports a range of operations, including searching for specific students, sorting data, and displaying departmental statistics.

## Features
- **Load Data**: Load student data from a text file (`internshipData.txt`).
- **Search**: Search for student records by name or full name.
- **Sort**: Sort records based on score or letter grade.
- **Statistics**: Display statistics on the number of students who passed or failed in each department.

## File Format (`internshipData.txt`)
The data file should contain records in the following format:

- `name`: The student's first name.
- `surname`: The student's last name.
- `departmentCode`: The department code (355, 356, 365, 384).
- `semester`: The semester the student is enrolled in.
- `score`: The student's internship score.

## Functions
- `Load_InternshipDataTable`: Loads data from the file and stores it in a structure.
- `Display_InternshipDataTable`: Displays all internship data in a formatted table.
- `Search`: Searches for a student by name or full name and displays their details.
- `Sort`: Sorts the students by score or letter grade.
- `Statistics`: Displays the number of students who passed and failed in each department.

## Usage
1. Clone the repository to your local machine.
2. Ensure the file `internshipData.txt` is present in the same directory.
3. Compile and run the program:
   ```bash
   gcc internshipData.c -o internshipData
   ./internshipData
