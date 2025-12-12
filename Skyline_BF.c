#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_BUILDINGS 1000

int SkylineAlgorithm(int buildings[][3], int n, int skyline[][2])
{
    int p_total=0, points[2*n], temp;

    for (int i=0; i<n; i++)
    {
        points[p_total++] = buildings[i][0];
        points[p_total++] = buildings[i][1];
    }

    for (int i=0; i<p_total; i++)
        for (int j=0; j<p_total-i-1; j++)
            if (points[j] > points[j+1])
            {
                temp = points[j];
                points[j] = points[j+1];
                points[j+1] = temp;
            }

    int curr=0, prev_height=0;

    for (int i=0; i<p_total; i++)
    {
        int x_coord = points[i];
        int max_height = 0;

        for (int j=0; j<n; j++)
        {
            int left = buildings[j][0], right = buildings[j][1], height = buildings[j][2];

            if (left<=x_coord && x_coord<right && height>max_height)
                max_height = height;
        }

        if (curr==0 || max_height!=prev_height)
        {
            skyline[curr][0] = x_coord;
            skyline[curr][1] = max_height;
            curr++;
            prev_height = max_height;
        }

    }

    return curr;
}

int main(int argc, char *argv[])
{
    if (argc<2)
    {
        printf("Input file not provided.\n");
        return 1;
    }

    char dir[50] = "test_cases/";
    strcat(dir, argv[1]);

    FILE* input_file = fopen(dir, "r");

    if (input_file == NULL) {
        printf("No such file exists.\n");
        return 1;
    }

    int n, buildings[MAX_BUILDINGS][3], skyline[MAX_BUILDINGS*2][2];
    int curr = 0;

    if (fscanf(input_file, "%d\n", &n) != 1) {
        printf("Failed to read number of buildings.\n");
        fclose(input_file);
        return 1;
    }

    char line[256];
    int line_no = 0;
    while (curr < n && fgets(line, sizeof(line), input_file) != NULL)
    {
        int a, b, c;
        int parsed = sscanf(line, "%d %d %d", &a, &b, &c);

        if (parsed != 3) {
            printf("input line [%d] doesn't contain exactly 3 elements\n", line_no+2);
            fclose(input_file);
            return 1;
        }

        if (a < 0 || b < 0 || c < 0) {
            printf("input line [%d] has invalid data\n", line_no+2);
            fclose(input_file);
            return 1;
        }

        if (b <= a) {
            printf("input line [%d] has right x-coordinate < left x-coordinate\n", line_no+2);
            fclose(input_file);
            return 1;
        }

        if (c <= 0) {
            printf("input line [%d] has height <= 0\n", line_no+2);
            fclose(input_file);
            return 1;
        }

        buildings[curr][0] = a;
        buildings[curr][1] = b;
        buildings[curr][2] = c;

        curr++;
        line_no++;
    }

    if (curr < n) {
        printf("Input contained fewer building entries (%d) than expected (%d).\n", curr, n);
        fclose(input_file);
        return 1;
    }

    clock_t start_time = clock();
    int count = SkylineAlgorithm(buildings, n, skyline);
    clock_t end_time = clock();

    printf("Skyline: { ");
    for (int k = 0; k < count; k++)
        printf("{%d, %d}, ", skyline[k][0], skyline[k][1]);
    printf("}\n");

    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);

    fclose(input_file);
    return 0;
}