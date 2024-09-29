#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_management.h"

void display_menu() {
    printf("\n==== Secure File Storage Menu ====\n");
    printf("1. Add New User/Go to existing User\n");
    printf("2. Add File to Existing User\n");
    printf("3. Read a File\n");
    printf("4. List files for a user\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    char username[50];
    char filename[50];
    char data[1024]; // Buffer for file content
    int choice;
    int user_exists = 0;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Add New User
                printf("Enter new username to register: ");
                scanf("%s", username);

                // Check if user already exists
                if (check_user_directory_exists(username)) {
                    printf("User %s already exists. Welcome back!\n", username);
                    user_exists = 1;
                } else {
                    if (register_user(username) == 0) {
                        //printf("User %s registered successfully!\n", username);
                        user_exists = 1;
                    } else {
                        printf("Failed to register user %s.\n", username);
                    }
                }
                break;

            case 2: // Add File to Existing User
                if (!user_exists) {
                    printf("Please register or select an existing user first.\n");
                } else {
                    printf("Enter filename to upload: ");
                    scanf("%s", filename);

                    printf("Enter data for file: ");
                    getchar(); // To consume the newline character left by scanf
                    fgets(data, sizeof(data), stdin);

                    // Write content to file
                    if (write_to_file(username, filename, data) != 0) {
                        printf("Failed to write to file.\n");
                    } else {
                       // printf("File %s uploaded successfully for user %s!\n", filename, username);
                    }
                }
                break;

            case 3: 
		 // Read file contents
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter filename to read: ");
                scanf("%s", filename);
                read_file_contents(username, filename);
                break;

	 case 4:
                printf("Enter username: ");
                scanf("%s", username);
                if (check_user_directory_exists(username)) {
                    list_user_files(username); // Call function to list files
                } else {
                    printf("User does not exist. Please register first.\n");
                }
                break;

            case 5: // Exit
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}
