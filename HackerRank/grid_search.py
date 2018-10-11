#!/usr/bin/python

import sys


def print2Darray(arr):
	for row in arr:
		print row
	print

t = int(raw_input().strip())
for a0 in xrange(t):
	R,C = raw_input().strip().split(' ')
	#print "R,C",R,C
	R,C = [int(R),int(C)]
	R = int(R)		
	C = int(C)		
	G = []
	G_i = 0
	for G_i in xrange(R):
		G_t = str(raw_input().strip())
		G.append(G_t)
	#print2Darray(G)

	r,c = raw_input().strip().split(' ')
	r,c = [int(r),int(c)]
	P = []
	P_i = 0
	for P_i in xrange(r):
		P_t = str(raw_input().strip())
		P.append(P_t)
	#print2Darray(P)
	# look for pattern P in G
	i=0
	all_found=False
	row_found=0
	index_found_last = -1
	for row in range(R):
		pat = P[i]
		index_found = G[row].find(pat)
		if index_found != -1 and (index_found_last == index_found or index_found_last == -1):
			row_found += 1
			index_found_last = index_found 
			if (row_found == len(P)):
				all_found = True
				break
			i += 1				
		else:
			row_found=0
			index_found_last = -1
			i=0
			

	print "YES" if all_found else  "NO"
