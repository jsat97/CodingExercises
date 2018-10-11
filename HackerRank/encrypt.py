#!/usr/bin/python

import sys
import math


s = raw_input().strip()

rows = int(math.floor(math.sqrt(len(s))))
cols = int(math.ceil(math.sqrt(len(s))))

#print rows, cols

l=[s[i:i + cols] for i in range(len(s)) if i%cols == 0]	

for i in range(cols):
	line=""
	for j in l:
		if i < len(j): line += j[i]
	print line,
