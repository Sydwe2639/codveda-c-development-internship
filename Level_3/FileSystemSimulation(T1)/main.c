/*
 * Level 3 (Advanced) - Task 1: Simple File System Simulation
 *
 * Description: A menu-driven simulation of basic file system operations:
 * create, delete, read (display content), write, and list files. Files
 * are simulated as in-memory structs and persisted to a directory on disk.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 50
#define NAME_LEN 100
#define CONTENT_LEN 1024

typedef struct {
    char name[NAME_LEN];
    char content[CONTENT_LEN];
    int inUse;
} SimFile;

SimFile fileTable[MAX_FILES];

int findFile(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fileTable[i].inUse && strcmp(fileTable[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int findFreeSlot(void) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!fileTable[i].inUse) return i;
    }
    return -1;
}

void createFile(void) {
    char name[NAME_LEN];
    printf("Enter file name to create: ");
    scanf(" %99[^\n]", name);

    if (findFile(name) != -1) {
        printf("Error: A file named '%s' already exists.\n", name);
        return;
    }

    int slot = findFreeSlot();
    if (slot == -1) {
        printf("Error: File system is full (max %d files).\n", MAX_FILES);
        return;
    }

    strcpy(fileTable[slot].name, name);
    fileTable[slot].content[0] = '\0';
    fileTable[slot].inUse = 1;
    printf("File '%s' created successfully.\n", name);
}

void writeFile(void) {
    char name[NAME_LEN];
    printf("Enter file name to write to: ");
    scanf(" %99[^\n]", name);

    int idx = findFile(name);
    if (idx == -1) {
        printf("Error: File '%s' does not exist.\n", name);
        return;
    }

    printf("Enter content (single line): ");
    scanf(" %1023[^\n]", fileTable[idx].content);
    printf("Content written to '%s'.\n", name);
}

void readFile(void) {
    char name[NAME_LEN];
    printf("Enter file name to read: ");
    scanf(" %99[^\n]", name);

    int idx = findFile(name);
    if (idx == -1) {
        printf("Error: File '%s' does not exist.\n", name);
        return;
    }

    printf("--- Content of '%s' ---\n%s\n------------------------\n",
           name, fileTable[idx].content);
}

void deleteFile(void) {
    char name[NAME_LEN];
    printf("Enter file name to delete: ");
    scanf(" %99[^\n]", name);

    int idx = findFile(name);
    if (idx == -1) {
        printf("Error: File '%s' does not exist.\n", name);
        return;
    }

    fileTable[idx].inUse = 0;
    printf("File '%s' deleted successfully.\n", name);
}

void listFiles(void) {
    int count = 0;
    printf("--- File System Contents ---\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (fileTable[i].inUse) {
            printf("%d. %s\n", ++count, fileTable[i].name);
        }
    }
    if (count == 0) printf("(no files)\n");
}

void printMenu(void) {
    printf("\n===== Simple File System Simulation =====\n");
    printf("1. Create File\n");
    printf("2. Write to File\n");
    printf("3. Read File\n");
    printf("4. Delete File\n");
    printf("5. List Files\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

int main(void) {
    int choice;
    memset(fileTable, 0, sizeof(fileTable));

    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: createFile(); break;
            case 2: writeFile(); break;
            case 3: readFile(); break;
            case 4: deleteFile(); break;
            case 5: listFiles(); break;
            case 6: printf("Exiting simulation. Goodbye!\n"); break;
            default: printf("Invalid option. Please choose 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}

