//Berrak Yıldırım 2690964

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
inside of internshipData.txt:
name surname departmentCode semester score
Kaila Lembrick 355 20181 72.0
Xena Bosomworth 355 20191 75.0
Rhonda Eyam 356 20182 50.5
Lonny Koschek 365 20191 70.0
Carroll Laroze 365 20201 90.0
Elizabet Fabbro 384 20193 80.0
*/

struct internshipDataTable {
    char name[50];
    char surname[50];
    int departmentCode;
    int semester;
    double score;
    char letterGrade;
};

// My functions
struct internshipDataTable* Load_InternshipDataTable(FILE *fileName, int *total_students);
void Display_InternshipDataTable(struct internshipDataTable *table, int *total_students);
int Search(struct internshipDataTable *table, int *total_students, char *nameSurname);
void Sort (struct internshipDataTable *table, int *total_students);
void Statistics (struct internshipDataTable *table, int *total_students);


int main() { // MAIN FUNCTION
    FILE *file;

    // Asking for filename (if it is not internshipData.txt, ask again)
    char fileName[50];
    printf("\nEnter the filename:");
    fflush(stdin);
    scanf("%s", fileName);
    while (strcmp(fileName, "internshipData.txt") != 0) {
        printf("\nThis file does not exist. Please enter again:");
        fflush(stdin);
        scanf("%s", fileName);
    }

    // Total students
    int *pTotalStudents;
    int totalStudents;
    pTotalStudents = &totalStudents;

    // Function call
    struct internshipDataTable *table = Load_InternshipDataTable(file, pTotalStudents);

    // Function call for displaying table
    Display_InternshipDataTable(table, pTotalStudents);

    int choice = 0;
    while (choice !=4) { // Choose if you want to search, sort, look at the statistics or exit
        printf("\nWhat would you like to do?");
        printf("\n1 - search\n2 - sort\n3 - statistics\n4 - exit");
        printf("\nEnter your choice:");
        fflush(stdin);
        scanf("%d", &choice);

        if (choice == 1) { // Search name or fullname
            char fullname[40];
            printf("\nPlease enter the name of the student:");
            fflush(stdin);
            scanf("%s", fullname);

            // Function call to search
            int i = Search(table, pTotalStudents, fullname);

            // If function returns -1 (name is not in the table), ask for other name to search it again
            if (i == -1) {
                printf("\nThis student is not in our records!\n");
            } else { // Else function returned i which is the row of the table
                printf("\nname : %s\nsurname : %s\ndepartmentCode : %d\nsemester : %d\nscore : %.2lf\ngrade : %c\n",
                       table[i].name, table[i].surname, table[i].departmentCode, table[i].semester, table[i].score,
                       table[i].letterGrade);}}


        else if(choice == 2){ // Sort by the score or letter grade, and display
            Sort(table, pTotalStudents);
            Display_InternshipDataTable(table, pTotalStudents);}

        else if (choice == 3){ // Look at the statistics
            Statistics(table, pTotalStudents);}

        else if (choice == 4){ // Exit
            printf("\nByee!");
            return 0;}

        else { // Wrong input (any other choice than 1,2,3,4)
            printf("\nWrong input!");}}

    return 0;}


// Create an array, open a file and fill with array, close the file
struct internshipDataTable* Load_InternshipDataTable(FILE *fileName, int *total_students){
    fileName = fopen("internshipData.txt", "r");
    struct internshipDataTable *table = (struct internshipDataTable*) malloc(sizeof (struct internshipDataTable));

    if (fileName==NULL){ // Check if file is opening
        printf("File opening is unsuccessful");
        exit(-1);}

    char string[10000]; // Array

    int count = 0; // Row of the table

    while (fgets(string, 10000, fileName)){ // Fill the file with array
        fflush(stdin);
        fscanf(fileName,"%s %s %d %d %lf",
               table[count].name, table[count].surname, &table[count].departmentCode,
               &table[count].semester, &table[count].score);
        if (table[count].score >= 70.0)
            table[count].letterGrade = 'S';
        else
            table[count].letterGrade = 'U';

        count++;}

    *total_students = count; // Return size (total students) by reference

    fclose(fileName); // Close the file

    return table;} // Return the array


// Display the table
void Display_InternshipDataTable(struct internshipDataTable *table, int *total_students){
    printf("%-20s%-15s%-19s%-11s%s%14s\n", "name", "surname", "departmentCode", "semester", "score", "letterGrade\n");
    for (int i = 0; i < *total_students; i++) {
        printf("%-20s%-20s%-15d%-10d%.2f%8c\n",
               table[i].name, table[i].surname, table[i].departmentCode, table[i].semester, table[i].score, table[i].letterGrade);}}


// Search the name
int Search(struct internshipDataTable *table, int *total_students, char *nameSurname){
    char fullname[40];
    strcpy(fullname, nameSurname);

    // Get the name from fullname ('till it is empty)
    char *name = strtok(fullname, " ");
    // Anything else but name is surname
    char *surname = strtok(NULL, "");


    if (surname == NULL) { // If only name entered
        for (int i = 0; i < *total_students; i++) {
            if (strcmp(table[i].name, name) == 0) {
                return i;}} // Name found, return i (row of the table)

    } else { // Name and surname entered
        for (int i = 0; i < *total_students; i++) {
            if (strcmp(table[i].name, name) == 0 && strcmp(table[i].surname, surname) == 0) {
                return i;}}} // Fullname found, return i

    return -1;} // Name is not in the table


// Sort by the score or letter grade
void Sort (struct internshipDataTable *table, int *total_students){
    int column = 0;
    while (column!=1 && column!=2){
        printf("\nEnter your choice:");
        printf("\nWhich column (1: score, 2: letter grade)?:");
        fflush(stdin);
        scanf("%d", &column);
        if (column!=1 && column!=2) // If user chose column any other than 1 or 2
            printf("\nInvalid choice.");}

    if(column == 1) { // Sort by score
        for (int i = 0; i < *total_students - 1 ; i++) {
            for (int j=0 ; j <*total_students - 1 ; j++){
                if (table[j+1].score < table[j].score){ // Bublesort
                    struct internshipDataTable temp = table[j]; // Temp: temporarily stores the array
                    table[j] = table[j+1];
                    table[j+1] = temp;}}}}

    else if (column == 2){ // Sort by letter grade
        for (int i = 0; i < *total_students - 1 ; i++) {
            for (int j=0 ; j <*total_students - 1 ; j++){
                if (table[j+1].letterGrade < table[j].letterGrade){ // Bublesort
                    struct internshipDataTable temp = table[j];
                    table[j] = table[j+1];
                    table[j+1] = temp;}}}}}


// Display statistics
void Statistics(struct internshipDataTable *table, int *total_students){
    int passedCounter355 = 0, passedCounter356 = 0, passedCounter365 = 0, passedCounter384 = 0; // Passed student counters for the each course
    int failedCounter355 = 0, failedCounter356 = 0, failedCounter365 = 0, failedCounter384 = 0; // Failed student counters for the each course
    int totalStudentsPassed, totalStudentsFailed; // Total students who passed and failed

    for (int i=0 ; i<*total_students ; i++){ // i is the row of the array (table)
        if (table[i].departmentCode == 355){ // If department is 355 check for letter grade and count the students who passed and failed
            if (table[i].letterGrade == 'S')
                passedCounter355++;
            else
                failedCounter355++;}

        else if (table[i].departmentCode == 356){ // Else if department is 356 check for letter grade and count the students who passed and failed
            if (table[i].letterGrade == 'S')
                passedCounter356++;
            else
                failedCounter356++;}

        else if (table[i].departmentCode == 365){ // Else if department is 365 check for letter grade and count the students who passed and failed
            if (table[i].letterGrade == 'S')
                passedCounter365++;
            else
                failedCounter365++;}

        else if (table[i].departmentCode == 384){ // Else if department is 384 check for letter grade and count the students who passed and failed
            if (table[i].letterGrade == 'S')
                passedCounter384++;
            else
                failedCounter384++;}}
    totalStudentsPassed = passedCounter355 + passedCounter356 + passedCounter365 + passedCounter384; // Calculate the total students who passed
    totalStudentsFailed = failedCounter355 + failedCounter356 + failedCounter365 + failedCounter384; // Calculate the total students who failed

    // Display statistics
    printf("\nOverall: %d student(s) passed and %d student(s) failed!", totalStudentsPassed, totalStudentsFailed);
    printf("\nDepartment: 355, %d student(s) passed and %d student(s) failed!", passedCounter355, failedCounter355);
    printf("\nDepartment: 356, %d student(s) passed and %d student(s) failed!", passedCounter356, failedCounter356);
    printf("\nDepartment: 365, %d student(s) passed and %d student(s) failed!", passedCounter365, failedCounter365);
    printf("\nDepartment: 384, %d student(s) passed and %d student(s) failed!", passedCounter384, failedCounter384);}