#!/usr/bin/python
import sys

def PrintNo(no_fives, no_threes):
	no = ""
	for i in range(no_fives):
		no += '5'
	for i in range(no_threes):
		no += '3'
	print no


t = int(raw_input().strip())
for tno in xrange(t):
	n = int(raw_input().strip())
	if n < 3:
		print -1
		done = True
	else:				
		done = False
		if (n %3 == 0):
			PrintNo(n, 0)
			done = True
		else:	
			no_fives = n -1
			while(no_fives):
				no_threes= n - no_fives
				if (no_fives%3 == 0 and no_threes%5 == 0):
					PrintNo(no_fives, no_threes)
					done = True
					break
				no_fives -= 1

	if (not done):
		if (n %5 == 0):
				PrintNo(0, n)
		else:	
			print -1
			
