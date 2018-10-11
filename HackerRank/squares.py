#!/usr/bin/python

# Enter your code here. Read input from STDIN. Print output to STDOUT
import sys
import math

t = int(raw_input().strip())
for tno in xrange(t):
	A,B = raw_input().strip().split(' ')
	A,B = [int(A),int(B)]
	count = math.floor(math.sqrt(B)) - math.ceil(math.sqrt(A)) +1
	print int(count)
