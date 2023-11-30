# disco-ucas-project
CS F222 DISCO Project: University Course Assignment System

# DISCO Project : University Course Assignment System
### Collaborators : Somanshu Rath (2022A7PS0032G), Sanskar Mundhra (2022A7PS0757G), Aditya Sharma (2022A7PS1108G)

## Problem Statement 
The research problem at hand centers on optimizing the University Course Assignment System. Within a department, there exist "n" faculty members categorized into three distinct groups: "x1," "x2," and "x3." Faculty in each category are assigned different course loads, with "x1" handling 0.5 courses per semester, "x2" taking 1 course per semester, and "x3" managing 1.5 courses per semester.

In this system, faculty members possess the flexibility to take multiple courses in a given semester, and conversely, a single course can be assigned to multiple faculty members. When a course is shared between two professors, each professor's load is considered to be 0.5 courses. Moreover, each faculty member maintains a preference list of courses, ordered by their personal preferences, with the most preferred courses appearing at the top. Importantly, there is no prioritization among faculty members within the same category.

The primary objective of this research problem is to develop an assignment scheme that maximizes the number of courses assigned to faculty while aligning with their preferences and the category-based constraints ("x1," "x2," "x3"). The challenge lies in ensuring that a course can only be assigned to a faculty member if it is present in their preference list.

This problem is unique due to the flexibility it offers regarding the number of courses faculty members can take, distinct from typical Assignment problems. Potential modifications may include adjusting the maximum number of courses "y" for each category of professors, instead of requiring exact adherence, or extending the number of professor categories beyond the existing three to devise a more generalized solution.

## Our Approach
There are two very closely similar types of problems: matching problems and assignment problems. However we chose to go with the Hungarian Algorithm and implemented our logic using an adjacency matrix.
In our initial approach we have not given all possible combinations as output, on the contrary some assignments that our code finds *most* optimal.

The code first reads a list of courses from an input file. The code then reads a list of professors from the input file. For each professor, the code reads the professor's name, type, and courses. The code then constructs a matrix that represents the cost of assigning each course to each professor. The code then calls the solve function to find the minimum assignment of the matrix. Finally, the code prints the minimum assignment.

The code first defines a number of functions that are used to implement the Hungarian algorithm. The min_zero_row function finds the row with the fewest zeros in a zero matrix. The mark_matrix function finds the positions of the zeros in a matrix and marks them. The adjust_matrix function adjusts the matrix so that all rows have a minimum of zero and all columns have a minimum of zero. The hungarian_algorithm function implements the Hungarian algorithm to find the minimum assignment of a matrix.

The code then defines a function solve that takes a matrix as input and returns the minimum assignment of the matrix. The solve function first creates a copy of the matrix. Then, it calls the hungarian_algorithm function to find the minimum assignment of the matrix. Finally, it returns the corresponding assignments.