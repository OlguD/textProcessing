#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Text{
    char *text;
};

int getTextSize(char *text);
int getWordCount(char *text);
int getCharCount(char *text);

int main() {
    struct Text text;
    text.text = (char *)malloc(256 * sizeof (char));
    if (text.text == NULL){
        printf("Memory allocation failed.");
        return 1;
    }

    printf("Enter a sentence: ");
    fgets(text.text, 256, stdin);
    
    int countWord = getWordCount(text.text);
    int countChar = getCharCount(text.text);

    
    printf("\nWord Count: %d\n", countWord);
    printf("Char Count: %d\n", countChar);
    free(text.text);
    return 0;
}

int getTextSize(char *text){
    return strlen(text);
}

int getWordCount(char *text){
    int wordCount = 0;
    int textSize = getTextSize(text);
    for (int i=0; i<textSize; i++){
        if ((text[i] == ' ' || text[i] == '\n' || text[i] == '\t') && (i > 0 && text[i - 1] != ' ' && text[i - 1] != '\n' && text[i - 1] != '\t')) {
            wordCount++;
        }

        // To count the last word if the string does not end with space
        if (textSize > 0 && text[textSize - 1] != ' ' && text[textSize - 1] != '\n' && text[textSize - 1] != '\t') {
            wordCount++;
        }
    }
    return wordCount;
}

int getCharCount(char *text){
    int charCount = 0;
    for (int i=0; text[i]; i++){
        if (text[i] != ' ' && text[i] != '\0'){
            charCount ++;
        }
    }
    return charCount - 1; 
}