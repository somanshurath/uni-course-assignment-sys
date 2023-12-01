import numpy
from copy import deepcopy
from tabulate import tabulate


def min_zero_row(zero_matrix, mark_zero):
    """
    Finds the row in the zero_matrix with the fewest number of True values and marks the corresponding element as zero.

    Parameters:
    - zero_matrix (numpy.ndarray): The matrix containing boolean values.
    - mark_zero (list): A list of tuples representing the indices of the marked zeros.

    Returns:
    - None

    """ 
    

    min_row = [99999, -1]
    for row_no in range(zero_matrix.shape[0]):
        row_sum = numpy.sum(zero_matrix[row_no] == True)
        if row_sum > 0 and min_row[0] > row_sum:
            min_row = [numpy.sum(zero_matrix[row_no] == True), row_no]
    zero_index = numpy.where(zero_matrix[min_row[1]] == True)[0][0]
    mark_zero.append((min_row[1], zero_index))
    zero_matrix[min_row[1], :] = False
    zero_matrix[:, zero_index] = False


def mark_matrix(matrix):
    """
    Generates the function comment for the given function body in a markdown code block with the correct language syntax.

    Args:
        matrix (numpy.ndarray): The input matrix.

    Returns: 
        tuple: A tuple containing three lists:
            - marked_zero (list): A list of tuples representing the coordinates of the zero elements in the matrix that have been marked.
            - marked_rows (list): A list of row indices that have been marked.
            - marked_cols (list): A list of column indices that have been marked.
    """
    

    current_matrix = matrix
    zero_bool_matrix = (current_matrix == 0)
    zero_bool_matrix_copy = zero_bool_matrix.copy()
    marked_zero = []
    while (True in zero_bool_matrix_copy):
        min_zero_row(zero_bool_matrix_copy, marked_zero)
    marked_zero_row = []
    marked_zero_col = []
    for i in range(len(marked_zero)):
        marked_zero_row.append(marked_zero[i][0])
        marked_zero_col.append(marked_zero[i][1])
    non_marked_row = list(set(range(current_matrix.shape[0])) - set(marked_zero_row))
    marked_cols = []
    check_switch = True
    while check_switch:
        check_switch = False
        for i in range(len(non_marked_row)):
            row_array = zero_bool_matrix[non_marked_row[i], :]
            for j in range(row_array.shape[0]):
                if row_array[j] == True and j not in marked_cols:
                    marked_cols.append(j)
                    check_switch = True
        for row_no, col_no in marked_zero:
            if row_no not in non_marked_row and col_no in marked_cols:
                non_marked_row.append(row_no)
                check_switch = True
    marked_rows = list(set(range(matrix.shape[0])) - set(non_marked_row))
    return (marked_zero, marked_rows, marked_cols)


def adjust_matrix(mat, cover_rows, cover_cols):
    """
    Adjusts a matrix by subtracting the minimum non-zero element from each element in the matrix, 
    and then adding the minimum non-zero element to each element covered by the given rows and columns.

    Parameters:
    - mat (list of lists): The matrix to be adjusted.
    - cover_rows (list): The list of row indices to be covered.
    - cover_cols (list): The list of column indices to be covered.

    Returns:
    - list of lists: The adjusted matrix.
    """
    current_matrix = mat
    non_zero_element = []
    for row in range(len(current_matrix)):
        if row not in cover_rows:
            for i in range(len(current_matrix[row])):
                if i not in cover_cols:
                    non_zero_element.append(current_matrix[row][i])
    min_num = min(non_zero_element)
    for row in range(len(current_matrix)):
        if row not in cover_rows:
            for i in range(len(current_matrix[row])):
                if i not in cover_cols:
                    current_matrix[row, i] = current_matrix[row, i] - min_num
    for row in range(len(cover_rows)):
        for col in range(len(cover_cols)):
            current_matrix[cover_rows[row], cover_cols[col]
                    ] = current_matrix[cover_rows[row], cover_cols[col]] + min_num
    return current_matrix


def hungarian_algorithm(mat):
    """
    Generates a function comment for the given function body.

    Parameters:
    - mat: A numpy array representing the matrix to be processed.

    Returns:
    - ans_pos: A tuple representing the position of the answer.
    """
    dim = mat.shape[0]
    current_matrix = mat
    for row_no in range(mat.shape[0]):
        current_matrix[row_no] = current_matrix[row_no] - numpy.min(current_matrix[row_no])
    for col_no in range(mat.shape[1]):
        current_matrix[:, col_no] = current_matrix[:, col_no] - numpy.min(current_matrix[:, col_no])
    zero_count = 0
    while zero_count < dim:
        ans_pos, marked_rows, marked_cols = mark_matrix(current_matrix)
        zero_count = len(marked_rows) + len(marked_cols)
        if zero_count < dim:
            current_matrix = adjust_matrix(current_matrix, marked_rows, marked_cols)
    return ans_pos


def ans_calculation(mat, pos):
    """
    Calculates the total sum of the values in the given matrix at the specified positions.

    Args:
        mat (numpy.ndarray): The input matrix.
        pos (list): A list of tuples representing the positions in the matrix.

    Returns:
        tuple: A tuple containing the total sum of the values and a matrix with the values at the specified positions.
    """
    total = 0
    ans_mat = numpy.zeros((mat.shape[0], mat.shape[1]))
    for i in range(len(pos)):
        total += mat[pos[i][0], pos[i][1]]
        ans_mat[pos[i][0], pos[i][1]] = mat[pos[i][0], pos[i][1]]
    return total, ans_mat


def solve(Matrix):
    """
    Find the minimum sum in a given matrix.

    Parameters:
    - Matrix: a 2D list representing the matrix to find the minimum sum.

    Returns:
    - A list containing the minimum sum and the corresponding matrix.

    Example usage:
    ```python
    matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    result = solve(matrix)
    print(result)  # [15, [[0, 1, 0], [1, 0, 0], [0, 0, 1]]]
    ```
    """
    

    # The matrix who you want to find the minimum sum
    cost_matrix = Matrix
    ans_pos = hungarian_algorithm(cost_matrix.copy())
    ans, ans_mat = ans_calculation(cost_matrix, ans_pos)
    return [int(ans), ans_mat]


prof_dict = {}
profs = {}
error = 'No assignment possible, constraints'
N = 0
course_dict_1 = {}
course_dict_2 = {}


with open("input.txt") as input_data:
    ignore = input_data.readline()
    print('Hungarian Algorithm:\n\n')
    course_list = input_data.readline().split()
    print('List of Courses: ', course_list)
    L = len(course_list) * 2
    cnt = 0
    for i in range(L):
        course_dict_1[i] = course_list[i // 2]
        course_dict_2[course_list[i // 2]] = [i - i % 2, i - i % 2 + 1]
    hungarian_matrix = numpy.ones(shape=(L, L)) * 1000
    while 1:
        professor = input_data.readline().split()
        if professor:
            cnt += 1
            print('Professor ', cnt, ':')
            print(professor)
            name, category = professor[0], float(professor[1])
            profs[name] = [category, set()]
            x = int(category//0.5)
            for i in range(x):
                prof_dict[N + i] = name
            prof_pref_courses = professor[2:]
            for i in range(len(prof_pref_courses)):
                hungarian_matrix[course_dict_2[prof_pref_courses[i]]
                                 [0]][N: N + x] = i + 1
                hungarian_matrix[course_dict_2[prof_pref_courses[i]]
                                 [1]][N: N + x] = i + 1
            N += x
        else:
            break

from tabulate import tabulate
if N != L:
    print(error)
else:
    M, Solution = solve(hungarian_matrix)
    if M >= 1000:
        print('\n\n', error)
    else:
        print("\nMost Optimal Assignment(s) :")
        answer_set = []
        def Solve(solution):
            """
            Generates a unique solution based on the given solution.

            Parameters:
                solution (list of lists): The solution to be used for generating a unique solution.

            Returns:
                None
            """
            answer = deepcopy(profs)
            for i in range(N):
                for j in range(N):
                    if solution[i][j]:
                        course = course_dict_1[i]
                        answer[prof_dict[j]][1].add(course)
            if answer not in answer_set:
                answer_set.append(answer)

        Solve(Solution)
        for i in range(N):
            for j in range(N):
                original = hungarian_matrix[i][j]
                hungarian_matrix[i][j] = 1000
                m, Solution = solve(hungarian_matrix)
                if m == M:
                    Solve(Solution)
                hungarian_matrix[i][j] = original
        if len(answer_set) == 0:
            print("No valid assignments found.")
        else:
            print("Optimal Assignments:")
            for idx, answer in enumerate(answer_set, start=1):
                print(f"\nAssignment {idx}:")
                table_data = []
                for professor, courses in answer.items():
                    table_data.append([professor, ', '.join(courses[1])])
                print(tabulate(table_data, headers=['Professor', 'Assigned Courses'], tablefmt='grid'))