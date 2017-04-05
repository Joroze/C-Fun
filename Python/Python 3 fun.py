# CSCI 310 - Procedural/Object-Oriented Assignment (using Python 3)
# Author: Jordan Rosenberg
# 3/27/2017
# --------------------------------------

# Function: hlbackwards
# Description: Takes a list as input, and returns a list in which the elements of the toplevel list are in reverse order
def hlbackwards(nList):
  if len(nList) == 0:
    return nList
  else:
    return nList[::-1]
# --------------------------------------

# Function: is_list
# Description: Returns a boolean depending on if the input is a list or not
def is_list(p):
  return isinstance(p, list)

# Function: llbackwards
# Description: Takes a list as input, and returns a list in which every list and sublist is in reverse order. 
def llbackwards(nList):
  rList = []
  for sublist in nList:
    if (is_list(sublist)):
      rList.append(llbackwards(sublist))
    else:
      rList.append(sublist)
  rList.reverse()
  return rList
# --------------------------------------

# Function: palindrome
# Description: Takes a list as input and returns the list if the list is a palindrome, 
# ie reads the same in both directions, and otherwise returns the original list made into a 
# palindrome by reversing it and appending it to itself, but not replicating the last element.  
def palindrome(nList):
  rList = nList[:] # creates new copy of nList and assigns to rList
  rList = llbackwards(rList)[:] # reverses rList
  
  if (rList == nList):
    return nList
  else:
    del rList[0]
    nList.append(rList)
    return nList
# --------------------------------------

# Function: permutations
# Description: Takes a list as input and generates a list containing all possible permutations of the list elements
def permutations(nList):
  from itertools import permutations # (useful permutations library)
  pList = []
  for perm in permutations(nList):
      pList.append([perm])
  return pList
# --------------------------------------

# Function: ionah (Tower of Hanoi solution)
# Description: Take single number as input and prints out the solution to the inverted disk problem for that many disks. 
# This is the problem of moving a stack of k disks of increasing size from bottom to top, from the first peg to the third peg with 
# another peg that may be used as well, subject to the condition that a smaller disk is never put on top of a larger one, 
# and only one disk may be moved at a time

# Main function that calls the helper (recHanoi)
def ionah(n):
  recHanoi(n,3,1,2)  
 
def recHanoi(n, to, From, u):
    if (n > 0):
        recHanoi(n-1, u, From, to)
        print("Move disk from peg '{}' to peg '{}'".format(From, to))
        recHanoi(n-1, to, u, From)
# --------------------------------------

# Function: sequence
# Description: Main function that takes a single integer as input and prints out a list containing that many terms of the sequence defined by...
def sequence(n): # Main function
  sList = []
  if (n == 2):
    return [0] + [1]
  elif (n > 2):
    # Store the value of the seqDef and append to a list, recursively
    r = [seqDef(n)]
    sList = sequence(n - 1) + r
  return sList

# Function: seqDef
# Description: Helper function that defines the sequence...
def seqDef(n):
    if (n == 1):
        return 0
    elif (n == 2):
        return 1
    elif (n > 2):
        r = 2 * seqDef(n - 1) + seqDef(n - 2)
        return r
# --------------------------------------

# Function: argue
# Description: A program that argues with the user, accepts a list as input
# Example input: >>> argue(['you','are','a','stupid','computer'])
def argue(nList):
  for i in range(0, len(nList)):
    if nList[i] == 'you':
      nList[i] = 'i'
    elif nList[i] == 'i':
      nList[i] = 'you'
    elif nList[i] == 'am':
      nList[i] = 'are not'
    elif nList[i] == 'are':
      nList[i] = 'am not'
    elif nList[i] == 'are not':
      nList[i] = 'am'
    elif nList[i] == 'is':
      nList[i] = 'is not'
    elif nList[i] == 'is not':
      nList[i] = 'is'
    elif nList[i] == 'your':
      nList[i] = 'my'
    elif nList[i] == 'my':
      nList[i] = 'your'
    elif nList[i] == 'does':
      nList[i] = 'does not'
    elif nList[i] == 'does not':
      nList[i] = 'does'
  return nList
# --------------------------------------

# Function: bubblesort
# Description: Takes a list of numbers as input and returns the list sorted in ascending order using a bubblesort. 
def bubblesort(nList):
  temp = []
  for i in range(len(nList) - 1, 0 , - 1):
    for j in range(i):
      if nList[j] > nList[j + 1]:
        temp = nList[j]
        nList[j] = nList[j + 1]
        nList[j + 1] = temp
  return nList
# --------------------------------------


# Testing each function output
print(hlbackwards([1,[2,3],[[4,5,[6],7],8,9]]))
print(llbackwards([1,[2,3],[[4,5,[6],7],8,9]]))
print(palindrome([1,2,3,[2],1]))
print(palindrome([1,[2,3,[4]],[[4],3,2],1]))
print(permutations([1,2,3]))
print(ionah(3))
print(sequence(7))
print(argue(['you','are','a','stupid','computer']))
print(argue(['you','are']))
print(argue(['are']))
print(argue(['i', 'am', 'a', 'smart', 'human']))
print(argue(['your', 'mother', 'does', 'wear', 'army', 'boots']))
print(argue(['you', 'are', 'argumentative']))
print(bubblesort([1,4,2,8,6,7]))

