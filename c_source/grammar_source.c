#include "grammar_source.h"

//swap funcion, used to swap values in array to sort
void swap(char **simmilar_words, int index1, int index2)
{
    char *temp = simmilar_words[index1];
    simmilar_words[index1] = simmilar_words[index2];
    simmilar_words[index2] = temp;
}
//function min returns smalles of three ints
int min(int a, int b, int c)
{
    if(a<= b && a<=c) return a;
    if(b<=a && b<=c) return b;
    return c;
}
//implementing wagner_fisher algorithm to calculate "distance" betwenn words
//more on that algorithm https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
int wagner_fisher(const char * word1, const char * word2)
{
    int n = strlen(word1);
    int m = strlen(word2);
    int **matrix = calloc(n+1, sizeof(int*));
    for(int i = 0; i<n+1; i++)
        matrix[i] = calloc(m+1, sizeof(int));
    for(int i = 0; i<=n; i++)
        matrix[i][0] = i;
    for (int i = 0; i<=m; i++)
        matrix[0][i] = i;
    for (int i = 1; i<=n; i++)
    {
        for(int j =1; j<=m; j++)
        {
            int cost = (word1[i-1]==word2[j-1]) ? 0 : 1;
            matrix[i][j] = min(matrix[i-1][j]+1, matrix[i][j-1]+1, matrix[i-1][j-1] + cost);
        }
    }
    int response = matrix[n][m];
    for(int i = 0; i<n+1; i++)
        free(matrix[i]);
    free(matrix);
    return response;
}
//get words gets words that are nearest of target word, and return an array
void get_words(char ** simmilar_words, char word[46], char * path, int how_much)
{
    // printf("%d Zuzia3", how_much); 

    char (*loaded)[46] = malloc(370099 * 46);
    FILE *f = fopen(path, "r");
    int counter = 0;
    while (counter < 370099 && fgets(loaded[counter], 46, f))
    {
        loaded[counter][strcspn(loaded[counter], "\n")] = 0;
        counter++;
    }
    fclose(f);
    int * scores = malloc(how_much * sizeof(int));
    // printf("%d Zuzia4", how_much); 
    for(int i = 0; i<how_much; i++)
        scores[i] = INT_MAX;
    // printf("%d Zuzia5", how_much); 
    for(int i = 0; i<counter; i++)
    {
        int score = wagner_fisher(loaded[i], word);
        for (int j = 0; j<how_much; j++)
        {
            if(score < scores[j])
            {
                scores[j] = score;
                strcpy(simmilar_words[j], loaded[i]);
                break;
            }
        }
    }
    // printf("%d Zuzia6", how_much); 
    //bubble sort, no more than 100 operations usually O(n) not gonna change it
    for (int a = 0; a < how_much - 1; a++) 
    {
        for (int b = 0; b < how_much - a - 1; b++) {
            if (scores[b] > scores[b+1]) {
                int temp = scores[b];
                scores[b] = scores[b+1];
                scores[b+1] = temp;
                swap(simmilar_words, b, b+1);
            }
    }
    }
    // printf("%d Zuziax", how_much); 
    free(scores);
    free(loaded);
    return; 
}
//check_words checks if word is in the english language
bool check_word(char * word, char * path)
{
    //debug case:
    // printf("%d Zuzia", path); 
    bool res = false;
    char (*loaded)[46] = malloc(370099 * 46);
    FILE *f = fopen(path, "r");
    int counter = 0;
    while (counter < 370099 && fgets(loaded[counter], 46, f))
    {
        loaded[counter][strcspn(loaded[counter], "\n")] = 0;
        counter++;
    }
    fclose(f);
    int left = 0;
    int right = 370098;
    while (left <= right)
    {
        int center = (left+right)/2;
        int diff = strcmp(loaded[center], word);
        if(diff == 0)
        {
            res = true;
            break;
        }
        if (diff<0)
            left = center+1;
        else if(diff>0)
            right = center-1;
        
    }
    free(loaded);
    return res;
}
//this function alocates memory and runs get_words function
char ** seek_corects(char * word, char * path, int how_much)
{
    // printf("%d Zuzia1", how_much); 
    char ** words_out = calloc(how_much, sizeof(char*));
    for(int i = 0; i<how_much; i++)
    {
        words_out[i] = calloc(46, sizeof(char));
    }
    get_words(words_out, word, path, how_much);
    // printf("%d Zuzia2", how_much); 
    return words_out;   
}
//this free_words function frees memory alocated in seek_corects
void free_words(char ** words, int how_much)
{
    // printf("%d Zuziafree", how_much); 
    for(int i = 0; i<how_much; i++)
        free(words[i]);
    free(words);
}
//©Copyright 2025 Stanisław Kulesza Poland