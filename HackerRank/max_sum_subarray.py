#!/usr/bin/python

import sys
# Enter your code here. Read input from STDIN. Print output to STDOUT
n = (int)(raw_input().strip())
a = [i for i in raw_input().strip().split()]

mx_init = -sys.maxint - 1
mx_list = []
mx = mx_init
sum = int(a[0])
j = 1
#print a
#for  j in range(1,n):
while True:
  i = int(a[j])
  if i == 0:
    mx_list.append(mx)
    mx = mx_init
    if j == n-1: break 
    j += 1
    sum = int(a[j])
  else:
    try_sum = sum + i
    if try_sum < sum:
      mx = max(mx, sum)
      sum = i
    elif i > 0 and sum < 0:
      sum = i
    else:
      sum = try_sum
    if j == n-1: 
      mx = max(mx, sum)
      mx_list.append(mx)
      break
  j += 1
  print "i, sum, max", i, sum, mx        

print mx_list
print max(mx_list)
