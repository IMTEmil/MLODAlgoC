#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHUNK_SIZE_MAX 5

typedef struct String
{
    unsigned int chunkSize;

    char chunk[CHUNK_SIZE_MAX];

    void *next;

} String;

// à faire du style: typedef String *String pour etre conforme à l'image

String *string_new(char *word);

String *string_new(char *word)
{   
    unsigned int length_word = strlen(word);
    unsigned int i = 0;

    String *string = (String *) malloc(sizeof(String));
    String *next = {0};

    if (length_word > CHUNK_SIZE_MAX)
    {
        string->chunkSize = CHUNK_SIZE_MAX;
        next = string_new(word + CHUNK_SIZE_MAX);
        string->next = (String*)next;
    } 
    else {
        string->chunkSize = length_word;
    }

    for (i = 0; i < length_word; i++)
    {
        string->chunk[i] = word[i];
    }

    return string;
}

void printString(String *string)
{
    unsigned int i = 0;
    String *iterString = string;

    while (iterString != NULL)
    {
        for (i = 0; i < iterString->chunkSize; i++)
        {
            fprintf(stdout, "%c", iterString->chunk[i]);
        }
        iterString = iterString->next;
    }
}

void printlnString(String *string)
{
    printString(string);
    fprintf(stdout, "\n");
}

unsigned int string_length(String *string)
{
    unsigned int length = 0;
    String *iterString = string;

    while (iterString != NULL)
    {
        length += iterString->chunkSize;
        iterString = iterString->next;
    }
    return length;
}

/*
String *string_insert_at(String *string, unsigned int index, char *word)
{
    unsigned int slength =  string_length(string) + 1;
    unsigned int i = 0; 
    String *iterString = string;

    if (index > slength) return string;
    if (index == slength)
    {
        string->next = string_new(word);
    }
    else 
    {
        while (i < index - CHUNK_SIZE_MAX)
        {
            i += iterString->chunkSize;
            iterString = iterString->next;
        }

        iterString->next = string_new(word);
    }
    return string;
}
*/

int main(int argc, char** argv)
{
    String *s = string_new("HELLO !");
    
    unsigned int size = string_length(s);

    printString(s);

    printlnString(s);

    fprintf(stdout, "size : %u\n", size);

    // s = string_insert_at(s, 7, "les pros du C");

    return 0;
}