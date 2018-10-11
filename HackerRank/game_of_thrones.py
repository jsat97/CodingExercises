#!/usr/bin/python

import sys
import string

found = True
# Write the code to find the required palindrome and then assign the variable 'found' a value of True or False

s = raw_input().strip()
#length = len(s)
#print "length =", length

dict = {k:0 for k in string.ascii_lowercase}
for i in string.ascii_lowercase:
	dict[i] = s.count(i)

odd = False
for i in s:
	if dict[i] % 2 != 0:
		if (odd and i != odd_one):
			found = False
			break
		odd_one = i
		#print "odd_one =", odd_one
		odd = True
if not found:
    print("NO")
else:
    print("YES")

