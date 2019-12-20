#Determine current workstation and select cwd accordingly.
import os
homePCDir = os.path.isfile('input.txt')
laptopDir = os.path.isfile('input.txt')

#Function to get instructions as a list
def getInst():
    with open('input.txt') as file:
        inst = file.readlines()
        return inst

#Function for creating a coordinate list
def appendcoords(x, y, coordinates):
    coordinates.append(f'{x}:{y}')
    return coordinates

#Function for plotting wire path to the coordinate list
def wirePath(wireStr):
    #Use Regex to split the directions into two sets, one for direction, one for distance
    import re
    dir = re.findall("[UDLR]", wireStr)
    dist = re.findall("[0-9]+", wireStr)   

    #define starting coordinates and split for loop into different scenarios for x or y changes
    x1 = 0
    y1 = 0
    coordinates = list()
    for index, letter in enumerate(dir): 
        x2 = ""
        y2 = ""
        if letter == 'R':
            x2 = x1 + int(dist[index])
            while x1 != x2:
                x1 += 1
                appendcoords(x1, y1, coordinates)
        if letter == 'L':
            x2 = x1 - int(dist[index])
            while x1 != x2:
                x1 -= 1
                appendcoords(x1, y1, coordinates)
        if letter == 'U':
            y2 = y1 + int(dist[index])
            while y1 != y2:
                y1 += 1
                appendcoords(x1, y1, coordinates)
        if letter == 'D':
            y2 = y1 - int(dist[index])
            while y1 != y2:
                y1 -= 1
                appendcoords(x1, y1, coordinates)
    return coordinates

#Function for finding closest coordinates
def manhatDist(funcList):
    i = 0
    currentNum = False
    for x in funcList: #I think there are much better ways to do this but I couldn't figure it out and I don't want to break anything now. particularly I don't know what significance x has at all.
        testNum = abs(funcList[i]) + abs(funcList[i+1])
        if currentNum == False or testNum < currentNum:
            currentNum = testNum
        if i + 2 >= len(funcList):
            return currentNum
        else:
            i += 2

#function to count steps of a match for two wires
def countSteps(matchList, wireList1, wireList2):
    #recombine matchList to compare with wire paths; at this point I realize this is obviously not effecient but I've dug a hole that I'll keep digging for now.
    combinedMatches = []
    i = 0
    finalDist = 0
    for x in matchList:
        combinedMatches.append(f'{matchList[i]}:{matchList[i + 1]}')
        if i + 2 >= len(matchList):
            break
        i += 2
    for k in combinedMatches: 
        for index1, num1 in enumerate(wireList1):
            if k == num1:
                dist1 = int(index1 + 1)
                for index2, num2 in enumerate(wireList2):
                    if k == num2:
                        dist2 = int(index2 + 1)
                        currentDist = dist1 + dist2
                        if finalDist == 0 or currentDist < finalDist:
                            finalDist = currentDist
    return finalDist                            

#find matches and return a list of them
def findMatch(wirePath1, wirePath2):
    matches = set(wirePath1).intersection(set(wirePath2))
    matchList = []
    while len(matches) > 0:
        currentCoord = matches.pop()
        tempList = [int(x) for x in currentCoord.split(':')]
        matchList.append(tempList[0])
        matchList.append(tempList[1])
    return matchList

#Create object for each wire's instructions
instList = getInst()
firstWire = instList[0]
secondWire = instList[1]

#lists of coordinates for each wire
firstWirePath = wirePath(firstWire)
secondWirePath = wirePath(secondWire)

#matches
matchList = findMatch(firstWirePath, secondWirePath)

#Answer Part 1
partOneAnswer = manhatDist(matchList)
print(f'The answer to part 1 is: {partOneAnswer}')

#Answer Part 2
partTwoAnswer = countSteps(matchList, firstWirePath, secondWirePath)
print(f'The answer to part 2 is: {partTwoAnswer}')