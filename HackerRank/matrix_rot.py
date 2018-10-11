#!/usr/bin/python

import sys


def print2Darray(arr, m, n):
	for row in range(m):
		for col in range(n):
			print arr[row][col],
		print


def CopyArray(from_arr, to_arr, m, n):
	for row in range(m):
		for col in range(n):
			to_arr[row][col] = from_arr[row][col]
	
	
def top_left_edge(i, j, row_start, row_end, col_start, col_end):
	if (i == row_start and j == col_start): return True
	return False

def bot_left_edge(i, j, row_start, row_end, col_start, col_end):
	if (i == row_end and j == col_start): return True
	return False

def top_right_edge(i, j, row_start, row_end, col_start, col_end):
	if (i == row_start and j == col_end): return True
	return False

def bot_right_edge(i, j, row_start, row_end, col_start, col_end):
	if (i == row_end and j == col_end): return True
	return False

m,n,r = raw_input().strip().split(' ')
m=int(m)
n=int(n)
r=int(r)
M=[n*[0] for i in range(m)]
for i in xrange(m):
	val = str(raw_input().strip())
	#M.append(val)
	val = val.split(' ')
	for j in range(len(val)):
		M[i][j] = int(val[j])

min_row = 0
min_col = 0
max_row = m
max_col = n

#print "min_row min_col max_row max_col", min_row, min_col, max_row, max_col
for rot in range(r):
	#print "matrix before rotation #", rot
	#print2Darray(M)

	Mnew=[n*[0] for i in range(m)]
	while(True):
		for i in range(min_row, max_row):
			for j in range(min_col, max_col):
				#print "rot, i,j", rot, i, j
				if (j == min_col):
					if (bot_left_edge(i, j, min_row, max_row-1, min_col, max_col-1)): 
						Mnew[i][j+1] = M[i][j]
					else:
						Mnew[i+1][j] = M[i][j]

				if (i == max_row -1):
					if (bot_right_edge(i, j, min_row, max_row-1, min_col, max_col-1)):
						Mnew[i-1][j] = M[i][j]
					else:
						Mnew[i][j+1] = M[i][j]

				if (j == max_col -1):
					if (top_right_edge(i, j, min_row, max_row-1, min_col, max_col-1)):
						Mnew[i][j-1] = M[i][j]
					else:
						Mnew[i-1][j] = M[i][j]

				if (i == min_row):
					if (top_left_edge(i, j, min_row, max_row-1, min_col, max_col-1)):
						Mnew[i+1][j] = M[i][j]
					else:
						Mnew[i][j-1] = M[i][j]

		#rotate the next inner rectangle
		min_row += 1
		min_col += 1
		max_row -= 1
		max_col -= 1

		if (min_row > max_row or min_col > max_col):
			break

	#copy the rotated array into the original for next rotation, Mnew will be reinitialized
	#print "matrix after rotation #", rot
	#print2Darray(Mnew)
	CopyArray(Mnew, M, m, n)
	#reset min, max values to original for the next rotation
	min_row = 0
	min_col = 0
	max_row = m
	max_col = n
	
#print final array
print2Darray(Mnew, m, n)
