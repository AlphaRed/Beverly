#include"common.h"
#include "text.h"
#include "gfx.h"

FILE *openTextFile(char *filename) {
    FILE *file = fopen(filename, "r");

    if(file == NULL) {
        printf("Failed to load text file, %s\n", filename);
        return NULL;
    }
    else
        return file;
}

void closeTextFile(FILE *f) {
    fclose(f);
}

void loadText(FILE *f, String_t *str) { // doesn't seem to work the second time through...
    fgets(str->data, MAX_CHARS, f);
    str->index = 0;
    str->len = 0;
    for(int i = 0; str->data[i] != '\n'; i++) {
        str->len++;
    }
    printf("string: %s\n", str->data);
    printf("length: %d\n", str->len);
}