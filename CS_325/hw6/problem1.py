#!/bin/python3

import scipy.optimize

totalNodeCount = 0

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
    return -1

def FindEnds (startingNodes):
    global totalNodeCount
    ends = []
    for start in startingNodes:
        for item in distances:
            if item['start'] == start:
                ends.append({'start' : start, 'end' : item['end']})
                totalNodeCount += 1
    return ends

def FindMinPath(start, end):
    global totalNodeCount
    totalNodeCount = 0
    # find contraints
    searching = True
    startingNodes = [start]
    nodes = []
    while (searching):
        newEnds = FindEnds (startingNodes)

        startingNodes = []
        for testEnd in newEnds:
            #print (testEnd)
            startingNodes.append(testEnd['end'])
            if testEnd['end'] == end:
                searching = False

        for node in newEnds:
            nodes.append(node)

    # generate matricies
    #print ("total nodes: " + str(totalNodeCount))
    #print (nodes)
    
    c = []
    A = []
    B = []

    for aIndex in range (0, totalNodeCount) :
        arrayBuilder = []
        for bIndex in range (0, totalNodeCount) :
            arrayBuilder.append([])
        A.append(arrayBuilder)

    index = 0
    for node in nodes:
        c.append(1)
        if node['end'] == end:
            B.append(-1)
        elif node['start'] == start:
            B.append(1)
        else:
            B.append(0)

        #print (node)
        for aIndex in range (0, totalNodeCount) :
            #print ("---")
            #print (aIndex)
            #print (len(nodes))
            #print (nodes[aIndex])
            x = nodes[aIndex]['start']
            y = node['end']
            A[aIndex][index] = (- FindDistance(x, y) + FindDistance(y, x))
            
        index += 1


    # solve
    #print ("c")
    #print (c)
    #print ("A")
    #print (A)
    #print ("B")
    #print (B)
    res = scipy.optimize.linprog(c,A,B)

    # multiply-sum the elements of x with the distances to get the distance
    index = 0
    totalDistance = 0
    sumDistance = 0
    for x in res.x:
        
        if x > 0:
            sumDistance += FindDistance(nodes[index]['start'], nodes[index]['end']) * x
            sumDistance *= 1/x

        totalDistance += sumDistance
            
        index += 1

    #print (totalDistance)

    return str(totalDistance)

# find a path from G to all other nodes with the minimum distance
for destLoop in range(ord('a'), ord('h') + 1):
    if destLoop == ord('g'):
        continue
    dest = chr (destLoop)
    print ("g->" + dest + " = " + FindMinPath('g', dest))
