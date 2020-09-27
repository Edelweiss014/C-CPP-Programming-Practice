#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void rotateMatrix(char matrix[10][10], char temp[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            temp[j][9 - i] = matrix[i][j];
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
    return;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "Error matrix!\n");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Error matrix!\n");
        return EXIT_FAILURE;
    }
    char matrix[10][10]; 
    char str[12];
    for (int i = 0; i < 10; i++) {
        if (fgets(str, 12, f) != NULL) {
            char * findNewLine = strchr(str, '\n');
            if (findNewLine == NULL || findNewLine - str != 10){
                fprintf(stderr, "Error matrix!\n");
                return EXIT_FAILURE;
            }
            else {
                for (int j = 0; j < 10; j++) {
                    matrix[i][j] = str[j];
                }
            }
        }
    }
    int c; c = fgetc(f);
    if ((c = fgetc(f)) != EOF) {
        fprintf(stderr, "Error matrix!\n");
        return EXIT_FAILURE;
    }
    char temp[10][10];
    rotateMatrix(matrix, temp);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
    if (fclose(f) != 0) {
        fprintf(stderr, "Error closing file!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
