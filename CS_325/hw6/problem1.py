#!/bin/python3

distances = [
    {'start':'g', 'end':'d', 'distance':2},
    {'start':'g', 'end':'h', 'distance':3},
    {'start':'h', 'end':'a', 'distance':4},
    {'start':'h', 'end':'b', 'distance':9},
    {'start':'a', 'end':'f', 'distance':10},
    {'start':'a', 'end':'b', 'distance':8},
    {'start':'d', 'end':'f', 'distance':18},
    {'start':'b', 'end':'e', 'distance':10},
    {'start':'f', 'end':'b', 'distance':7},
    {'start':'f', 'end':'a', 'distance':5},
    {'start':'b', 'end':'c', 'distance':4},
    {'start':'f', 'end':'c', 'distance':3},
    {'start':'c', 'end':'d', 'distance':3},
    {'start':'e', 'end':'g', 'distance':7},
    {'start':'d', 'end':'e', 'distance':25},
    {'start':'e', 'end':'d', 'distance':9},
    {'start':'f', 'end':'e', 'distance':2}
]

def FindDistance (start, end):
    for item in distances:
        if item['start'] == start and item['end'] == end:
            return item['distance']

def FindMinPath(start, end):
    # find contraints

    # compute matrix

    # solve
    return str(111)

# find a path from G to all other nodes with the minimum distance
for destLoop in range(ord('a'), ord('h') + 1):
    if destLoop == ord('g'):
        continue
    dest = chr (destLoop)
    print ("g->" + dest + " = " + FindMinPath(dest, 'g'))
