#ifndef TEXT_H
#define TEXT_H

extern Client_t client;

FILE *openTextFile(char *filename);
void closeTextFile(FILE *f);
void loadText(FILE *f, String_t *str);

#endif