#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEMENTS_PER_ARRAY 3
#define MIN_VALUE 10
#define MAX_VALUE 100

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <NUM_BUILDINGS>\n", argv[0]);
        return 1;
    }

    int NUM_BUILDINGS = atoi(argv[1]);
    if (NUM_BUILDINGS <= 0) {
        printf("NUM_BUILDINGS must be a positive integer.\n");
        return 1;
    }

    srand(time(NULL));

    int (*buildings)[ELEMENTS_PER_ARRAY] = malloc(NUM_BUILDINGS * sizeof(*buildings));
    if (buildings == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < NUM_BUILDINGS; i++)
    {
        buildings[i][0] = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;

        int min_second = buildings[i][0] + 1;

        if (min_second > MAX_VALUE)
            buildings[i][1] = buildings[i][0]+10;
        else
            buildings[i][1] = (rand() % (MAX_VALUE - min_second + 1)) + min_second;

        buildings[i][2] = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
    }

    char filename[100];
    sprintf(filename, "test_cases/buildings_tc_%d_inputs.txt", NUM_BUILDINGS);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to create file.\n");
        free(buildings);
        return 1;
    }

    fprintf(fp, "%d\n", NUM_BUILDINGS);

    for (int i = 0; i < NUM_BUILDINGS; i++)
        fprintf(fp, "%d %d %d\n", buildings[i][0], buildings[i][1], buildings[i][2]);

    fclose(fp);
    free(buildings);

    printf("File generated: %s\n", filename);

    return 0;
}
