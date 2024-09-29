#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include<dirent.h>
#include <errno.h>

// Function to create the base uploads directory
int create_base_directory() {
    if (mkdir("uploads", 0755) == -1 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        return -1; // Error creating base directory
    }
    return 0; // Success
}

// Function to create a user directory
int create_user_directory(const char *username) {
    char path[256]; // Adjust size as needed
    snprintf(path, sizeof(path), "./uploads/%s", username);

    // Create the user directory
    if (mkdir(path, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create user directory");
        return -1; // Error creating user directory
    }

    return 0; // Success
}

// Function to check if the user directory already exists
int check_user_directory_exists(const char *username) {
    // Construct the user directory path
    char user_directory[256];
    snprintf(user_directory, sizeof(user_directory), "./uploads/%s", username);

    DIR* dir = opendir(user_directory);
	if (dir) {
    /* Directory exists. */
    	closedir(dir);return 1;
	} else if (ENOENT == errno) {
    /* Directory does not exist. */
		return 0;
	} else {
    /* opendir() failed for some other reason. */
	}	
    return 0; // Directory does not exist
}


// Function to register a user
int register_user(const char *username) {
    if (create_base_directory() != 0) {
        return -1; // Failed to create base directory
    }    
    if (check_user_directory_exists(username)) {
        printf("Welcome back, %s!\n", username); // User already exists
        return 0;
    }

    if (create_user_directory(username) != 0) {
        return -1; // Failed to create user directory
    }

    printf("User %s registered successfully!\n", username);
    return 0; // Success
}

// Function to upload a file
int upload_file(const char *username, const char *filename,const char *data) {
    char filepath[256]; // Adjust size as needed
    snprintf(filepath, sizeof(filepath), "./uploads/%s/%s", username, filename);

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Failed to upload file");
        return -1; // Error uploading file
    }

    // For demonstration purposes, write a simple message
    //fprintf(file, "%s", data);

    printf("File %s uploaded successfully for user %s!\n", filename, username);
    return 0; // Success
}

// Function to list files in the user directory
void list_files(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "ls ./uploads/%s", username);
    printf("Files for user %s:\n", username);
    system(command);
}

// Function to write data into a file
int write_to_file(const char *username, const char *filename, const char *data) {
    // Construct the full path for the file within the user's directory
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./uploads/%s/%s", username, filename);

    // Open the file for writing ("w" mode overwrites if it exists)
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filepath);
        return -1; // File open error
    }

    // Write the content to the file
    fprintf(file, "%s", data);

    // Close the file
    fclose(file);

    printf("File %s uploaded successfully for user %s!\n", filename, username);
    return 0; // Success
}

// Function to read and print the contents of a file
void read_file_contents(const char *username, const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./uploads/%s/%s", username, filename);

    // Open the file in read mode
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s for reading.\n", filepath);
        return;
    }

    // Read and print the file contents
    char ch;
    printf("Contents of the file %s:\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n");

    // Close the file
    fclose(file);
}

void list_user_files(const char *username) {
    char path[256];
    snprintf(path, sizeof(path), "./uploads/%s", username);

    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Error: Unable to open directory for user %s\n", username);
        return;
    }

    struct dirent *entry;
    printf("Files for user %s:\n", username);
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

// Add more functionalities (like download, delete) as needed
