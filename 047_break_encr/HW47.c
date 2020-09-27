
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int findKey(int * alphaFreq) {
    int key = 0; 
    for (int i = 0; i < 26; i++) {
        if (alphaFreq[key] < alphaFreq[i]) key = i;
    }
    key = key - 4; 
    if (key < 0) key += 26;
    return key;
}

int breakKey(FILE * f) {
    int key = 0;
    int alphaFreq[26] = { 0 };
    int c;
    while((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            c = tolower(c);
            alphaFreq[c - 'a']++;
        }
    }
    key = findKey(alphaFreq);
    return key;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        perror("Insufficient or exceeding arguments!\n");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Error opening file!\n");
        return EXIT_FAILURE;
    }
    int key = breakKey(f);
    printf("%d\n", key);
    if (fclose(f) != 0) {
        perror("Error closing file!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
