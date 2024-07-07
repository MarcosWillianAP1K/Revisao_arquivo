#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceStringInFile(const char *filename, const char *oldString, const char *newString) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Determine the size of the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory to hold the file content
    char *fileContent = (char *)malloc(fileSize + 1);
    if (fileContent == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    // Read the file content into the buffer
    fread(fileContent, 1, fileSize, file);
    fileContent[fileSize] = '\0';
    fclose(file);

    // Find and replace the old string with the new string
    char *position = strstr(fileContent, oldString);
    if (position != NULL) {
        // Calculate the lengths of the strings
        size_t oldStringLength = strlen(oldString);
        size_t newStringLength = strlen(newString);
        size_t newFileSize = fileSize - oldStringLength + newStringLength;

        // Allocate memory for the new file content
        char *newFileContent = (char *)malloc(newFileSize + 1);
        if (newFileContent == NULL) {
            perror("Memory allocation failed");
            free(fileContent);
            return;
        }

        // Copy the content before the old string
        size_t prefixLength = position - fileContent;
        strncpy(newFileContent, fileContent, prefixLength);

        // Copy the new string
        strcpy(newFileContent + prefixLength, newString);

        // Copy the content after the old string
        strcpy(newFileContent + prefixLength + newStringLength, position + oldStringLength);

        // Write the new content back to the file
        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            free(fileContent);
            free(newFileContent);
            return;
        }

        fwrite(newFileContent, 1, newFileSize, file);
        fclose(file);

        free(newFileContent);
    } else {
        printf("String not found in the file.\n");
    }

    free(fileContent);
}

int main() {
    const char *filename = "example.txt";
    const char *oldString = "old_text";
    const char *newString = "new_text";

    FILE *arq = fopen(filename, "a");
    fclose(arq);

    replaceStringInFile(filename, oldString, newString);

    return 0;
}