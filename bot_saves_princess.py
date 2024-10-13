import math

def find_element(element, grid):
    for i in grid:
        for j in i:
            if element == j:
                return (grid.index(i), i.index(j))

def distance_calc(a, b):
    return math.sqrt((b[0]-a[0])**2 + (b[1]-a[1])**2)

def displayPathtoPrincess(n,grid):
    index_m = find_element("m", grid)
    index_p = find_element("p", grid)
    moves = ""
    while index_m != index_p:
        curr_distance = distance_calc(index_m, index_p)
        lowest = curr_distance
        if distance_calc((index_m[0]-1, index_m[1]), index_p) <= lowest:
            index_m = (index_m[0]-1, index_m[1])
            moves += "UP\n"
            curr_distance = distance_calc(index_m, index_p)
            lowest = curr_distance
        if distance_calc((index_m[0]+1, index_m[1]), index_p) <= lowest:
            index_m = (index_m[0]+1, index_m[1])
            moves += "DOWN\n"
            curr_distance = distance_calc(index_m, index_p)
            lowest = curr_distance
        if distance_calc((index_m[0], index_m[1]-1), index_p) <= lowest:
            index_m = (index_m[0], index_m[1]-1)
            moves += "LEFT\n"
            curr_distance = distance_calc(index_m, index_p)
            lowest = curr_distance
        if distance_calc((index_m[0], index_m[1]+1), index_p) <= lowest:
            index_m = (index_m[0], index_m[1]+1)
            moves += "RIGHT\n"
            curr_distance = distance_calc(index_m, index_p)
            lowest = curr_distance
    print(moves)
    return moves

m = int(input())
grid = [] 
for i in range(0, m): 
    grid.append(input().strip())

displayPathtoPrincess(m,grid)
