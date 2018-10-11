#!/usr/bin/python

import sys


def print2Darray(arr, m, n):
	for row in range(m):
		this_row = ""
		for col in range(n):
			#print arr[row][col],
			this_row += arr[row][col]
		print this_row

n = raw_input().strip()
n=int(n)
M=[n*[0] for i in range(n)]
for i in xrange(n):
	val = str(raw_input().strip())
	for j in range(len(val)):
		M[i][j] = val[j:j+1]

#print2Darray(M, n, n)
for i in range(n):
	this_row = ""
	for j in range(n):
		this_val = M[i][j]
		if (i > 0 and j > 0 and i < n-1 and j < n-1):
			if (M[i][j] > M[i-1][j] and M[i][j] > M[i][j-1] and M[i][j] > M[i+1][j] and M[i][j] > M[i][j+1] ):
				this_val = 'X'
		this_row += this_val

	print this_row
			
	
