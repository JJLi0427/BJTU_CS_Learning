#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILENAME_LENGTH 16
#define MAX_FILE_SIZE 1024

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    int start_block;
    int size;
    char data[MAX_FILE_SIZE];
} DirectoryEntry;

typedef struct {
    char volume_name[MAX_FILENAME_LENGTH];
    int total_blocks;
    int free_blocks;
    DirectoryEntry* directory;
    char current_path[MAX_FILENAME_LENGTH];
} FileSystem;

FileSystem fs;

void formatDisk() {
    printf("Enter volume name: ");
    scanf("%s", fs.volume_name);
    printf("Enter total number of blocks: ");
    scanf("%d", &fs.total_blocks);
    fs.free_blocks = fs.total_blocks;
    fs.directory = (DirectoryEntry*)malloc(sizeof(DirectoryEntry) * fs.total_blocks);
    for (int i = 0; i < fs.total_blocks; i++) {
        strcpy(fs.directory[i].filename, "");
        fs.directory[i].start_block = -1;
        fs.directory[i].size = 0;
    }
    strcpy(fs.current_path, "/");
    printf("Disk formatted successfully.\n");
}

void createDirectory() {
    char dirname[MAX_FILENAME_LENGTH];
    printf("Enter directory name: ");
    scanf("%s", dirname);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, "") == 0) {
            strcpy(fs.directory[i].filename, dirname);
            fs.directory[i].start_block = -1;
            fs.directory[i].size = 0;
            printf("Directory created successfully.\n");
            return;
        }
    }
    printf("No free space for directory creation.\n");
}

void changeDirectory() {
    char dirname[MAX_FILENAME_LENGTH];
    printf("Enter directory name: ");
    scanf("%s", dirname);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, dirname) == 0) {
            strcat(fs.current_path, dirname);
            strcat(fs.current_path, "/");
            
            printf("Directory changed to '%s'.\n", fs.current_path);
            return;
        }
    }
    printf("Directory '%s' not found.\n", dirname);
}

void renameDirectory() {
    char oldname[MAX_FILENAME_LENGTH], newname[MAX_FILENAME_LENGTH];
    printf("Enter old directory name: ");
    scanf("%s", oldname);
    printf("Enter new directory name: ");
    scanf("%s", newname);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, oldname) == 0) {
            strcpy(fs.directory[i].filename, newname);
            
            printf("Directory renamed successfully.\n");
            return;
        }
    }
    printf("Directory '%s' not found.\n", oldname);
}

void displayDirectory() {
    printf("Current Disk: %s\n", fs.volume_name);
    printf("Current Path: %s\n", fs.current_path);
    printf("Directory listing:\n");
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, "") != 0) {
            printf("- %s\n", fs.directory[i].filename);
        }
    }
}

void deleteDirectory() {
    char dirname[MAX_FILENAME_LENGTH];
    printf("Enter directory name: ");
    scanf("%s", dirname);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, dirname) == 0) {
            strcpy(fs.directory[i].filename, "");
            
            printf("Directory deleted successfully.\n");
            return;
        }
    }
    printf("Directory '%s' not found.\n", dirname);
}

void createFile() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter file name: ");
    scanf("%s", filename);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, "") == 0) {
            strcpy(fs.directory[i].filename, filename);
            fs.directory[i].start_block = i;
            fs.directory[i].size = 0;
            fs.directory[i].data[0] = '\0'; 
            fs.free_blocks--;
            printf("File created successfully.\n");
            return;
        }
    }
    printf("No free space for file creation.\n");
}

void renameFile() {
    char oldname[MAX_FILENAME_LENGTH], newname[MAX_FILENAME_LENGTH];
    printf("Enter old file name: ");
    scanf("%s", oldname);
    printf("Enter new file name: ");
    scanf("%s", newname);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, oldname) == 0) {
            strcpy(fs.directory[i].filename, newname);
            
            printf("File renamed successfully.\n");
            return;
        }
    }
    printf("File '%s' not found.\n", oldname);
}

void writeFile() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter file name: ");
    scanf("%s", filename);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, filename) == 0) {
            int block_index = fs.directory[i].start_block;
            
            if (block_index == -1) {
                printf("File '%s' not found.\n", filename);
                return;
            }
            printf("Enter file content:\n");
            char content[MAX_FILE_SIZE];
            scanf("%s", content);
            strcpy(fs.current_path, filename);
            fs.directory[i].size = strlen(content);
            strcpy(fs.directory[i].data, content); 
            printf("File '%s' written successfully.\n", filename);
            return;
        }
    }
    
    printf("File '%s' not found.\n", filename);
}

void displayFileContent() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter file name: ");
    scanf("%s", filename);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, filename) == 0) {
            printf("Content of file '%s':\n%s\n", filename, fs.directory[i].data);
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}

void deleteFile() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter file name: ");
    scanf("%s", filename);
    for (int i = 0; i < fs.total_blocks; i++) {
        if (strcmp(fs.directory[i].filename, filename) == 0) {
            strcpy(fs.directory[i].filename, "");
            fs.directory[i].start_block = -1;
            fs.directory[i].size = 0;
            fs.free_blocks++;
            printf("File deleted successfully.\n");
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}

int main() {
    int choice;
    printf("----------------------------------- FAT16 File System ----------------------------------\n");
    printf("1. Format Disk         2. Create Directory    3. Change Directory    4. Rename Directory\n");
    printf("5. Display Directory   6. Delete Directory    7. Create File         8. Rename File\n");
    printf("9. Write File         10. Display File       11. Delete File         0. Exit\n");
    do {
        printf("\nCurrent Disk: %s   Current Path: %s\n", fs.volume_name, fs.current_path);  
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: formatDisk(); break;
            case 2: createDirectory(); break;
            case 3: changeDirectory(); break;
            case 4: renameDirectory(); break;
            case 5: displayDirectory(); break;
            case 6: deleteDirectory(); break;
            case 7: createFile(); break;
            case 8: renameFile(); break;
            case 9: writeFile(); break;
            case 10: displayFileContent(); break;
            case 11: deleteFile(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    free(fs.directory);
    return 0;
}
