/*
 * Level 2 (Intermediate) - Task 1: Simple Student Management System
 *
 * Description: Console based program to manage student records (add,
 * delete, display, update), with file handling to persist data between
 * runs.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define FILENAME "students.dat"

typedef struct {
    int id;
    char name[NAME_LEN];
    float grade;
} Student;

Student students[MAX_STUDENTS];//Student records
int studentCount = 0;

// Load existing records from file into memory */
void loadRecords(void) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        studentCount = 0;
        return;
    }
    studentCount = (int)fread(students, sizeof(Student), MAX_STUDENTS, fp);
    fclose(fp);
}

// Save all records in memory back to file */
void saveRecords(void) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        printf("Error: could not open file for saving.\n");
        return;
    }
    fwrite(students, sizeof(Student), studentCount, fp);
    fclose(fp);
}

void addStudent(void) {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full!\n");
        return;
    }

    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);
    printf("Enter Grade: ");
    scanf("%f", &s.grade);

    students[studentCount++] = s;
    saveRecords();
    printf("Student added successfully.\n");
}

int findStudentIndex(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

void deleteStudent(void) {
    int id;
    printf("Enter ID of student to delete: ");
    scanf("%d", &id);

    int idx = findStudentIndex(id);
    if (idx == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    for (int i = idx; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    saveRecords();
    printf("Student deleted successfully.\n");
}

void updateStudent(void) {
    int id;
    printf("Enter ID of student to update: ");
    scanf("%d", &id);

    int idx = findStudentIndex(id);
    if (idx == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    printf("Enter new Name: ");
    scanf(" %49[^\n]", students[idx].name);
    printf("Enter new Grade: ");
    scanf("%f", &students[idx].grade);

    saveRecords();
    printf("Student updated successfully.\n");
}

void displayStudents(void) {
    if (studentCount == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-6s %-30s %-6s\n", "ID", "Name", "Grade");
    printf("--------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-6d %-30s %-6.2f\n", students[i].id, students[i].name, students[i].grade);
    }
    printf("\n");
}

void printMenu(void) {
    printf("\n===== Student Management System =====\n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Update Student\n");
    printf("4. Display All Students\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

int main(void) {
    int choice;

    loadRecords();

    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: deleteStudent(); break;
            case 3: updateStudent(); break;
            case 4: displayStudents(); break;
            case 5: printf("Exiting. Goodbye!\n"); break;
            default: printf("Invalid option. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
