#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Text {
    char *text;
    char buff[100000];
};

int getTextSize(const char *text);
int getWordCount(const char *text);
int getCharCount(const char *text);
void processInput(char *input);
void countFile(FILE *file, int *wordCount, int *charCount);

int main() {
    char input[256];
    printf("Enter a sentence or a filepath: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character from input if present
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    processInput(input);
    return 0;
}

void processInput(char *input) {
    struct Text text;
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (strstr(input, ".txt") != NULL) {
        FILE *file = fopen(input, "r");
        if (file == NULL) {
            printf("Failed to open file.\n");
            return;
        }

        int fileWordCount = 0, fileCharCount = 0;
        countFile(file, &fileWordCount, &fileCharCount);
        printf("File Word Count: %d\n", fileWordCount);
        printf("File Char Count: %d\n", fileCharCount);
        fclose(file);
    } else {
        text.text = malloc(256 * sizeof(char));
        if (text.text == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        strcpy(text.text, input);
        int countWord = getWordCount(text.text);
        int countChar = getCharCount(text.text);

        //printf("Input: %s\n", text.text);
        printf("Word Count: %d\n", countWord);
        printf("Char Count: %d\n", countChar);

        free(text.text);
    }
}

int getTextSize(const char *text) {
    return strlen(text);
}

int getWordCount(const char *text) {
    int wordCount = 0;
    int inWord = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isspace(text[i])) {
            if (inWord) {
                inWord = 0;
            }
        } else {
            if (!inWord) {
                inWord = 1;
                wordCount++;
            }
        }
    }
    return wordCount;
}

int getCharCount(const char *text) {
    int charCount = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (!isspace(text[i]) && text[i] != '\r') {
            charCount++;
        }
    }
    return charCount;
}

void countFile(FILE *file, int *wordCount, int *charCount) {
    char buffer[1000];
    *wordCount = 0;
    *charCount = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove trailing newline characters for consistent processing
        buffer[strcspn(buffer, "\r\n")] = '\0';
        *wordCount += getWordCount(buffer);
        *charCount += getCharCount(buffer);
    }
    
    // Ensure all characters are counted correctly, including those potentially missed in the last read
    if (ferror(file)) {
        printf("Error reading file\n");
    }
}
