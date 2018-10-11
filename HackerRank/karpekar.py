#!/usr/bin/python

import sys

start = int(raw_input().strip())
end = int(raw_input().strip())

found = False
for i in range (start, end +1):
	square = i**2
	val = square
	exp = len(str(i))
	div = 10**exp
	left = val/div
	right = val %div
	if (left + right) == i:
		print i,
		found = True
                
if not found:
	print "INVALID RANGE"
