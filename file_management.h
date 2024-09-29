#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

// Function to register a user
int register_user(const char *username);

int create_user_directory(const char *username);

// Function to upload a file
int upload_file(const char *username, const char *filename); // Assuming data is the file content

int write_to_file(const char *username, const char *filename, const char *data);

// Function to list files in the user directory
void list_user_files(const char *username);

int check_user_directory_exists(const char *username); // Declare the function

void read_file_contents(const char *username, const char *filename);

#endif // FILE_MANAGEMENT_H
