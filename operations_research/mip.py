from ortools.linear_solver import pywraplp

n = 3
nn = n + n
prime = []
multiply = 1
number = 2

while len(prime) < n:
    if all(number % i != 0 for i in range(2, number)):
        prime.append(number)
        multiply *= number
    number += 1

permutations = [[]]  # permute from 1 to nn - 1
for i in range(nn - 1):
    temp = []
    for permutation in permutations:
        for j in range(i + 1):
            temp.append(permutation[:j] + [i + 1] + permutation[j:])
    permutations = temp

for permutation in permutations:
    permutation = [
        0,
    ] + permutation  # start node is 0 ~ n - 1 & end node plus n

    length = [0] * n  # edge length clockwise
    count = [0] * nn
    category = [1] * nn
    for k in range(n):
        current = permutation[k]
        length[k] = (permutation[k + n] - permutation[k]) % nn
        for _ in range(length[k]):
            count[current] += 1
            category[current] *= prime[k]
            current = (current + 1) % nn

    solver = pywraplp.Solver.CreateSolver("SCIP")
    old, new, var = {}, {}, {}
    for i in range(nn):
        old[i] = solver.NumVar(1, 2, "")
        new[i] = solver.NumVar(1, 2, "")
        for j in range(i + 1, nn):
            var[i, j] = solver.IntVar(0, 1, "")

    # old_key = {0, 1, 2, ..., nn - 1}
    # new_key = {0, 1, 2, ..., nn - 1}
    # var_key = {(0, 1), (0, 2), ..., (0, nn - 1), (1, 2), ..., (nn - 2, nn - 1)}

    # old_sum >  old_com (first)
    # old_com >= old_sum (except first)
    # new_sum >= new_com (all)
    # old_i >= new_i (if count >= n-1)
    # old_i >= new_i or old_j >= new_j (if category_i * category_j % multiply == 0)

    small = 0.01
    values = [-small]
    for i in range(nn):
        values.append(old[i] if i < length[0] else -old[i])
    solver.Add(solver.Sum(values) >= 0)  # old_sum - old_com - small >= 0

    for k in range(1, n):
        values = []
        for i in range(nn):
            j = (i + permutation[k]) % nn
            values.append(-old[j] if i < length[k] else old[j])
        solver.Add(solver.Sum(values) >= 0)  # old_com - old_sum >= 0

    for k in range(n):
        values = []
        for i in range(nn):
            j = (i + permutation[k]) % nn
            values.append(new[j] if i < length[k] else -new[j])
        solver.Add(solver.Sum(values) >= 0)  # new_sum - new_com >= 0

    for i in range(nn):
        if count[i] >= n - 1:
            solver.Add(old[i] - new[i] >= 0)  # old_i - new_i >= 0

    big = 1e4
    for i in range(nn):
        for j in range(i + 1, nn):
            if category[i] * category[j] % multiply == 0:
                solver.Add(old[i] - new[i] + big * var[i, j] >= 0)
                solver.Add(old[j] - new[j] + big * (1 - var[i, j]) >= 0)
                # old_i - new_i + big * var_ij >= 0
                # old_j - new_j + big * (1 - var_ij) >= 0

    values = []
    for i in range(nn):
        values.append(old[i] if i < length[0] else -new[i])
    solver.Minimize(solver.Sum(values))  # minimize(old_sum - new_com)

    status = solver.Solve()
    if status == pywraplp.Solver.OPTIMAL or status == pywraplp.Solver.FEASIBLE:
        if solver.Objective().Value() <= 0:
            print(permutation)
            print(solver.Objective().Value(), "\n")

            for i in range(nn):
                print(old[i].solution_value(), end=", ")
            print("\n")

            for i in range(nn):
                print(new[i].solution_value(), end=", ")
            print("\n")

            for i in range(nn):
                for j in range(i + 1, nn):
                    print(var[i, j].solution_value(), end=", ")
                print("")
    # break
