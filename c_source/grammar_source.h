#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(char **simmilar_words, int index1, int index2);
int min(int a, int b, int c);
int wagner_fisher(const char * word1, const char * word2);
void get_words(char ** simmilar_words, char word[46], char * path, int how_much) ;
bool check_word(char * word, char * path);
char ** seek_corects(char * word, char * path, int how_much);
void free_words(char ** words, int how_much);


