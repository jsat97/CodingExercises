#!/usr/local/bin/python3

import sys
import os

"""
puzzle at -- http://www.opengarden.com/jobs.html
- Jai (jai_97@rediffmail.com)
30-Aug-2016
"""

def bsearch(arr, val):
  found = False
  low = 0
  mid = 0
  high = len(arr) -1
  while not found and low <= high:
    mid = int((low + high)/2)
    #print("low mid high = ", low,mid,high)
    if val < arr[mid]:
      high = mid -1
    elif val > arr[mid]:
      low = mid +1
    else:
      found = True
      #print("bsearch: found %d in %s" %(val, arr))
      break
  #return found, mid
  return found


def Print(depth, val):
  if depth > 1:
    print("%d + " %(val), end="")
  else:
    print("%d " %(val))
        

sorted = False

depth = 0


"""
recursively find sum of values in part of the array until we get the sum we need
start at the beginning of the array
loop through the array recursively and search the remainder of the sum or part thereof in the rest of the array 
if sum is not found and we reach the end of the array, start again at the next index of the array and do the same

a = array to search in
n = sum that we want
"""

def  SumPartialRecur(a, n):
  global sorted, depth
  found = False
  size_a = len(a)
  depth += 1
  if not sorted:
    a.sort()
    sorted = True

  #print("entry: depth = %d a = %s n = %d " %(depth, a, n))
  if not a:
    return False

  # search for n in a every time
  found = bsearch(a, n)
  if found:
    Print(depth, n)
    return found

  for i in range(size_a-1):
    rem = n - a[i]
    found = SumPartialRecur(a[i+1:], rem)
    depth -= 1
    if found:
      Print(depth, a[i])
      return found

  return found
 
## main ##

_a_cnt = 0
# no of values in the array
_a_cnt = int(input())
_a_i = 0
_a = []

#input the array
while _a_i < _a_cnt:
  _a_item = int(input());
  _a.append(_a_item)
  _a_i+=1

# sum we need 
_n = int(input())

res = SumPartialRecur(_a, _n)
