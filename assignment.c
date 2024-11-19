#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // WRITE YOUR CODE HERE
    if(argc > 3 || argc <= 2) 
    {  
        printf("%s", "Incorrect usage. You provided ");
        printf("%d", (argc - 1));
        printf("%s", " arguments. The correct number of arguments is 2\n");

        return 1;
    }

    int lengths[argc - 1];

    for (int i = 1; i < argc; i++) 
    {
        if (strlen(argv[i]) == 0) 
        {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            return 1; // empty string
        }

        char* p;
        errno = 0; // not 'int errno', because the '#include' already defined it
        long arg = strtol(argv[i], &p, 10);

        if (*p != '\0' || errno != 0 || arg > INT_MAX || arg < 1) 
        {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            return 1;
        }

        lengths[i - 1] = arg;
    }

    int** matrix;
    matrix = (int**) malloc(lengths[0]*sizeof(int*));
    for (int i = 0; i < lengths[0]; i++)
        matrix[i] = (int*) malloc(lengths[1]*sizeof(int));

    for (int x = 0; x < lengths[0]; x++)
    {
        for (int y = 0; y < lengths[1]; y++)
        {
            int randnum = minrand + rand() % maxrand;
            matrix[x][y] = randnum;
        }
    }
    
    FILE *f = fopen("matrix.txt", "ab+");

    if(f == NULL) 
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int x = 0; x < lengths[0]; x++)
    {
        for (int y = 0; y < lengths[1]; y++)
        {
            fprintf(f, "%d", matrix[x][y]);

            if(y + 1 < lengths[1])
                fprintf(f, "%s", " ");
        }

        if(x + 1 < lengths[0])
            fprintf(f, "%s", "\n");
        else
            fprintf(f, "%s", "\r");
    }

    for (int i = 0; i < lengths[0]; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    fclose(f);
    return 0;
}