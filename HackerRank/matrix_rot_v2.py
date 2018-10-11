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
	
#extract a rectangular slice of matrix into an array moving anti clock wise from left hand top edge
def GetMatrix(M, arr, row_start, row_end, col_start, col_end):
	count = 0
	for row in range(row_start, row_end +1):
		arr[count] = M[row][col_start]
		count += 1

	for col in range(col_start +1, col_end +1):
		arr[count] = M[row_end][col]
		count += 1

	for row in range(row_end -1, row_start -1, -1):
		arr[count] = M[row][col_end]
		count += 1

	for col in range(col_end -1, col_start, -1):
		arr[count] = M[row_start][col]
		count += 1

	#print "linear array from matrix (anti clockwise):", arr

#reverse of get
def PutMatrix(M, arr, row_start, row_end, col_start, col_end):
	count = 0
	for row in range(row_start, row_end +1):
		M[row][col_start]= arr[count] 
		count += 1

	for col in range(col_start +1, col_end +1):
		M[row_end][col] = arr[count]
		count += 1

	for row in range(row_end -1, row_start -1, -1):
		M[row][col_end] = arr[count]
		count += 1

	for col in range(col_end -1, col_start, -1):
		M[row_start][col] = arr[count]
		count += 1

	
def rotate(arr, left, right, nrot):
	#rotate only as much as needed
	length = len(arr)
	nrot_net = nrot % length 
	for irot in range(nrot_net):
		#rotate right
		if right:
			tmp = arr[length -1]
			for i in range(length -1, 0, -1):
				arr[i] = arr[i-1]
			arr[0] =tmp
		elif left:
			tmp = arr[0]
			for i in range(length -1):
				arr[i] = arr[i+1]
			arr[length -1] =tmp
	#print "array after %d rotations" %(nrot)
	#print arr


m,n,r = raw_input().strip().split(' ')
m=int(m)
n=int(n)
r=int(r)
M=[n*[0] for i in range(m)]
for i in xrange(m):
	val = str(raw_input().strip())
	#M.append(val)
	val = val.split(' ')
	length = len(val)
	for j in range(length):
		M[i][j] = int(val[j])

min_row = 0
min_col = 0
max_row = m -1
max_col = n -1

#print "min_row min_col max_row max_col", min_row, min_col, max_row, max_col
#print "matrix before rotation #", rot
#print2Darray(M)

Mnew=[n*[0] for i in range(m)]
while(True):
	arr = (2*( (max_row - min_row +1) + (max_col - min_col +1) ) - 4)*[0]
	GetMatrix(M, arr, min_row, max_row, min_col, max_col)						
	rotate(arr, 0, 1, r)
	PutMatrix(Mnew, arr, min_row, max_row, min_col, max_col)	
	#print2Darray(Mnew, m, n)

	min_row += 1
	min_col += 1
	max_row -= 1
	max_col -= 1

	if (min_row > max_row or min_col > max_col):
		break
	
#print final array
print2Darray(Mnew, m, n)
