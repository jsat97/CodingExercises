#!/usr/bin/python
import sys


t = int(raw_input().strip())
for t_no in xrange(t):
	n = int(raw_input().strip())
	a = int(raw_input().strip())
	b = int(raw_input().strip())

	l = [0]
	for i in range(1,n):
		l=(i+j for i in l for j in [a,b])

	l.sort()
	#print l
	l_uniq = ""
	old = ''
	for i in l:
		if i != old: 
			l_uniq += str(i) + " "
			old =i
	print l_uniq
