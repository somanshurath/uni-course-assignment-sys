# CS F222 DISCO Project : University Course Assignment System
### Collaborators : Somanshu Rath (2022A7PS0032G), Sanskar Mundhra (2022A7PS0757G), Aditya Sharma (2022A7PS1108G)

## Project Video
https://drive.google.com/file/d/18fihx7giht_eTOstPuwyxAZyXhsB2oe4/view?usp=sharing

## How to run the code?
We have utilized two algorithms for approaching the problem statement. 
#### 1. Heuristic Algorithm <br>
To run this algorithm, compile ```heuristic_approach.cpp```. <br>
To change test cases to run on it, select any test case from ```test_cases.txt``` (or make a custom test case) and copy-paste it to ```input.txt```. <br>
Then run the executable file and get the result in ```heuristic_output.txt```.
#### 2. Hungarian Algorithm <br>
To run this algorithm, run ```hungarian_approach.py```. <br>
To change test cases to run on it, select any test case from ```test_cases.txt``` (or make a custom test case) and copy-paste it to ```input.txt```. <br>
Output will be displayed in the terminal.



## Problem Statement 
The research problem at hand centers on optimizing the University Course Assignment System. Within a department, there exist "n" faculty members categorized into three distinct groups: "x1," "x2," and "x3." Faculty in each category are assigned different course loads, with "x1" handling 0.5 courses per semester, "x2" taking 1 course per semester, and "x3" managing 1.5 courses per semester.

In this system, faculty members possess the flexibility to take multiple courses in a given semester, and conversely, a single course can be assigned to multiple faculty members. When a course is shared between two professors, each professor's load is considered to be 0.5 courses. Moreover, each faculty member maintains a preference list of courses, ordered by their personal preferences, with the most preferred courses appearing at the top. Importantly, there is no prioritization among faculty members within the same category.

The primary objective of this research problem is to develop an assignment scheme that maximizes the number of courses assigned to faculty while aligning with their preferences and the category-based constraints ("x1," "x2," "x3"). The challenge lies in ensuring that a course can only be assigned to a faculty member if it is present in their preference list.

## Our Approaches

#### Heuristic Algorithm Approach
This approach gives us mutliple (not-optimized) assignments. It randomly shuffles the list of professors and assigns them one course at a time, until all the slots are fulfilled. This approach gives out all possible permutations of assignments based on preference order and our approach. 


### Hungarian Algorithm Approach
This approach gives more optimized assignments. Here we have utilized the Hungarian algorithm, and implemented that logic to this situation. The overall assignment is more optimal and hence fewer in number.
