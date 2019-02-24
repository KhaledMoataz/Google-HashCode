import numpy as np

num = 0
files = ['a', 'b', 'c', 'd']
r = c = l = h = 0
arr = [[]]

#------------Taking the input------------
with open(files[num]+'.in') as f:
    r, c, l, h = [int(x) for x in next(f).split()]
    
    arr = []
    for line in f:
        a = []
        for x in line:
            if x == 'T': a.append(0)
            elif x == 'M': a.append(1)
        arr.append(a)
    arr = np.array(arr)

print('input::')
print(f'r = {r}, c = {c}, l = {l}, h = {h}')
print(f'arr = \n{arr}')

'''
H is the maximum area of the slice, 
and we want to maximize number of cells removed from the pizza.
So, we will work on sliding different windows of area H over all the pizza where each cell is its top left,
and if this slice is valid we will remove it from the pizza.
Areas = (H, 1), (1, H), (H/2, 2), (2, H/2),... and so on for the the factors of H.
General Formula: Area = (d, H/d) where d is a divisor of H, so that the window size will be exactly H.
So first we will get the factors
'''
#------------Getting the factors of H------------
i=1
factors = []
while i*i<=h:
    if (h%i == 0):
        factors.append(i)
        if (h/i != i):
            factors.append(int(h/i))
    
    i += 1

'''
1-  We check the validity of a certain window by counting the number of mushroom and tomates
    and checking that each of them is more than L.

2-  We already know that the window size is H, so this constraints won't be violated.

3-  We want also to check that there is no cells already taken from this window,
    So, we mark the taken cells by -1 as an indicator that they have been taken before 
    by another window.
'''
#------------Checking Validity------------
def valid(p1, p2):
    ones = 0
    for x in range(p1[0], p2[0]+1):
        for y in range(p1[1], p2[1]+1):
            ones += arr[x,y]
            if arr[x,y] == -1: return False

    zeroes = abs((p2[1] - p1[1]+1) * (p2[0] - p1[0]+1) - ones)
    return ones+zeroes <= h and ones >= l and zeroes >= l

#------------Sliding different windows------------
'''
It was found out by submitting different codes that working on different areas for the windows
other than windows with area exactly equal to H is better.
So, we will slide windows with areas equal to (d, H/d) where 1<= d <= H and d can be either a divisor of H or not.
'''
windows = []
# for factor in factors:
#     wl = factor-1
#     ww = int(h/factor)-1
for factor in range(1, h+1):
    wl = factor-1
    ww = int(h/factor)-1

    for row in range(r):
        if ww+row >= r: break

        for col in range(c):
            if wl+col >= c: break

            if valid((row, col), (row+ww, col+wl)):
                # make invalid
                for x in range(row, row+ww+1):
                    for y in range(col, col+wl+1):
                        arr[x,y] = -1
                
                windows.append(((row, col), (row+ww, col+wl),))

#------------Printing the Output------------
output = f'{len(windows)}\n'
for ((x, y), (x1, y1)) in windows: output += f'{x} {y} {x1} {y1}\n'

with open(files[num]+'.out', 'w') as f: f.write(output)
print(f'\noutput::\n{output}', end='')