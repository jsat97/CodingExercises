#!/usr/bin/python
import sys


n,m = raw_input().strip().split(' ')
n,m = [int(n),int(m)]
c = map(int,raw_input().strip().split(' '))
max_dist = -sys.maxint - 1
for i in range(n):
  min_dist_to_spc = sys.maxint
  if i in c:
    min_dist_to_spc = 0
  else:
    for j in range(m):
      min_dist_to_spc = min(abs(i - c[j]), min_dist_to_spc)
      if min_dist_to_spc == 1: break
  max_dist = max(min_dist_to_spc, max_dist)    

print max_dist     
