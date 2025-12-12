<h1>Skyline Problem with Brute Force and Divide-and-Conquer</h1>
This project was for my "Algorithm Analysis and Design" course. In this project, I came up with 2 algorithms for solving the skyline problem, analyse and compare the time and space complexity between the two algorithms and with the actual performances of their C program codes.


<h2>Brute Force Approach</h2>

- Create an array points[], by adding the left and right x-coordinates of every building,
- Sort points with increasing x-coordinates,
- For each x-coordinate in points compare with each building
    - IF x-coordinate is between left x-coordinate AND right x-coordinate of building, AND the height of the building is greater than max_height (max y-coordinate the current x-coordinate can have), THEN update the max_height to height of the building.
    - IF max_height is NOT equal to y-coordinate of previous element in skyline[][2] array, THEN add {x-coordinate, max_height} to the skyline[][2] array.


<h2>Divide and Conquer</h2>

- IF low index is equal to high index, THEN result_skyline[][2] = { {left x-coordinate of the building in low index, height of that building}, {{ {right x-coordinate of the building in low index, 0} } and return length of result_skyline[][2], which is 2 in this case.
- Find mid = (low + high) / 2
- Recursively find the skyline for input_set[low to mid], and input_set[mid+1 to high]
- Merge those two skylines like merging operation in Merge Sort algorithm:
    - Iterate an iterator in both the skylines (i and j)
        - IF ith x-coordinate of left_skyline < jth x-coordinate of right_skyline, THEN x-coordinate = ith x-coordinate of left_skyline, height1 = ith height of left_skyline, increase i by 1
        - ELSE IF ith x-coordinate of left_skyline > jth x-coordinate of right_skyline, THEN x-coordinate = jth x-coordinate of right_skyline, height2 = jth height of right_skyline, increase j by 1
        - ELSE (ith x-coordinate of left_skyline = jth x-coordinate of right_skyline), THEN x-coordinate = ith x-coordinate of left_skyline, height1 = ith height of left_skyline, height2 = jth height of right_skyline, increase i and j by 1.
    - Update max_height to max of height1 and height2.
    - IF the height of previous point in the result_skyline[][2] is NOT equal to max_height, THEN add {x-coordinate, max_height} to result_skyline[][2].
    - At one point, result_skyline[][2] would have all the points from either left_skyline or right_skyline. Now, we add the remaining points of the other skyline to the result_skyline[][2] by comparing height of previous point, and return the length of result_skyline[][2].


<h2>Input File Format</h2>

**File Format:** TEXT File (.txt)<br>
First line contains only 1 integer, which is the input array size *n* representing the number of buildings in the input set.<br>
Next *n* lines contain exactly 3 positive integers in each line, seperated by a single space. *First integer* is the *left x-coordinate* of the building, *second integer* is the *right x-coordinate* of the building, and *third integer* is the *height* of the building.

Example.<br>
5<br>
2 9 10<br>
3 7 15<br>
5 12 12<br>
15 20 10<br>
19 24 8<br>

Here, *n=5*, which means 5 buildings in the input set.<br>
*1st* building has *left x-coordinate=2*, *right x-coordinate=9*, *height=10*.<br>
*2nd* building has *left x-coordinate=3*, *right x-coordinate=7*, *height=15*.<br>
So on upto *nth* building.

<h2>Compilation Commands</h2>

- **Brute Force:** gcc Skyline_BF.c -o Skyline_BF
- **Divide and Conquer:** gcc Skyline_DandC.c -o Skyline_DandC
- **Large Input Array Generator:** gcc large_input_array_generator.c -o generate_inputs

<h2>Execution Commands</h2>
Before running the following commands, make sure there is a folder called <b>test_cases</b>, and put the input files in that folder. The <b>Large Input Array Generator</b> generates an input file in required format for the two algorithms, having desired number of elements for input array.

- **Brute Force:** Skyline_BF *input_file_name*
- **Divide and Conquer:** Skyline_DandC *input_file_name*
- **Large Input Array Generator:** generate_inputs *desired_input_array_size*