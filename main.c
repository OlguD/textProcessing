#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Text{
    char *text;
};

int getTextSize(char *text);
int getWordCount(char *text);


int main() {
    struct Text text;
    text.text = (char *)malloc(256 * sizeof (char));
    if (text.text == NULL){
        printf("Memory allocation failed.");
        return 1;
    }

    printf("Enter a sentence: ");
    fgets(text.text, 256, stdin);

    int count = getWordCount(text.text);

    printf("\nCount: %d\n", count);
    return 0;
}

int getTextSize(char *text){
    return strlen(text);
}

int getWordCount(char *text){
    int wordCount = 0;
    int textSize = getTextSize(text);
    for (int i=0; i<textSize; i++){
        if (text[i] == '\0' && text[i + 1] == '\0'){
            break;
        } else{
            if (text[i] != '\0'){
                wordCount += 1;
            }
        }
    }
    return wordCount;
}
