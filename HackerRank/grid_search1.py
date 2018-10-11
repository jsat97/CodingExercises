#!/usr/bin/python

import sys


no_tests = int(raw_input().strip())
#print no_tests
for i in xrange(no_tests):
	grid_rows,grid_cols = raw_input().strip().split(' ')
	#print grid_rows, grid_cols
	grid_rows,grid_cols = [int(grid_rows),int(grid_cols)]
	G = []
	for j in range(grid_rows):
		j = raw_input().strip()
		G.append(j)
	pat_rows,pat_cols = raw_input().strip().split(' ')
	pat_rows,pat_cols = [int(pat_rows),int(pat_cols)]
	print pat_rows, pat_cols
	P = []
	for j in range(pat_rows):
		j = raw_input().strip()
		P.append(j)
	#print P
