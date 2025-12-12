#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_BUILDINGS 1000

int MergeSkylines(int left_skyline[][2], int n1, int right_skyline[][2], int n2, int result_skyline[][2]) 
{ 
    int height1 = 0, height2 = 0, i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) 
    {
        int x_coord, max_height;

        if (left_skyline[i][0] < right_skyline[j][0]) 
        {
            x_coord = left_skyline[i][0];
            height1 = left_skyline[i][1];
            i++;
        } 
        
        else if (left_skyline[i][0] > right_skyline[j][0]) 
        {
            x_coord = right_skyline[j][0];
            height2 = right_skyline[j][1];
            j++;
        } 

        else 
        {
            x_coord = left_skyline[i][0];
            height1 = left_skyline[i][1];
            height2 = right_skyline[j][1];
            i++;
            j++;
        }

        max_height = (height1 > height2) ? height1 : height2;

        if (k == 0 || result_skyline[k - 1][1] != max_height) {
            result_skyline[k][0] = x_coord;
            result_skyline[k][1] = max_height;
            k++;
        }
    }

    while (i < n1) 
    {
        if (k == 0 || result_skyline[k - 1][1] != left_skyline[i][1]) {
            result_skyline[k][0] = left_skyline[i][0];
            result_skyline[k][1] = left_skyline[i][1];
            k++;
        }
        i++;
    }

    while (j < n2) 
    {
        if (k == 0 || result_skyline[k - 1][1] != right_skyline[j][1]) {
            result_skyline[k][0] = right_skyline[j][0];
            result_skyline[k][1] = right_skyline[j][1];
            k++;
        }
        j++;
    }

    return k; 
 
}

int SkylineAlgorithm(int buildings[][3], int low, int high, int result_skyline[][2]) 
{ 

    if (low == high)
    {

        int left = buildings[low][0]; 
        int right = buildings[low][1]; 
        int height = buildings[low][2]; 

        result_skyline[0][0] = left; 
        result_skyline[0][1] = height; 
        result_skyline[1][0] = right; 
        result_skyline[1][1] = 0;

        return 2;
    }

    int mid = (low + high) / 2; 

    int left_skyline[MAX_BUILDINGS][2];
    int right_skyline[MAX_BUILDINGS][2];

    int n1 = SkylineAlgorithm(buildings, low, mid, left_skyline);
    int n2 = SkylineAlgorithm(buildings, mid + 1, high, right_skyline);

    return MergeSkylines(left_skyline, n1, right_skyline, n2, result_skyline);
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
    int count = SkylineAlgorithm(buildings, 0, n-1, skyline);
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