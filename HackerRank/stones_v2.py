#!/usr/bin/python
import sys
import math


t = int(raw_input().strip())
for t_no in xrange(t):
	n = int(raw_input().strip())
	a = int(raw_input().strip())
	b = int(raw_input().strip())

	low = min(a,b) *(n-1)
	high = max(a,b)*(n-1)				
	diff =  abs(a - b)
	cur = low
	output = str(low)
	if (a != b):
		while (True):
			cur += diff			
			output += " " + str(cur)
			if (cur == high): break	

	print output
