#!/usr/bin/python
import sys

def print2Darray(arr, m, n):
	for row in range(m):
		for col in range(n):
			print arr[row][col],
		print

m,n = raw_input().strip().split(' ')
m,n = [int(m),int(n)]
#print "m,n",m,n
M=[n*[0] for i in range(m)]
for i in xrange(m):
  val = str(raw_input().strip())
  for j in range(len(val)):
    if (list(val)[j] == 'G'):
      M[i][j] = 1
    else:
		  M[i][j] = 0
print2Darray(M, m, n)

BigPlus=set() #contains sets of all possible regions (+ or a single cell). each of these contains one or more cells

for i in range(m):
  for j in range(n):
    if M[i][j]:
      Plus = set()
      Plus.add((i,j)) 
      #this cell is center of a plus ?  add all cells in the plus to the set Plus
      #up = set((k,j) for k in range(i-1,-1,-1) if M[k][j] == 1)
      up = set()
      down = set()
      left = set()
      right = set()
      dist_up = 0
      dist_down = 0
      dist_left = 0
      dist_right = 0

      for k in range(i-1,-1,-1): 
        if M[k][j] == 0: break
        up.add((k,j))
        dist_up = i - k
      #down = set((k,j) for k in range(i+1,m) if M[k][j] == 1)
      if dist_up == 0: continue
      dist = dist_up

      for k in range(i+1,i+dist): 
        if M[k][j] == 0: break
        down.add((k,j))
        dist_down = k - i
      if dist_down == 0: continue
      dist = min(dist, dist_down)

      #left = set((i,k) for k in range(j-1,-1,-1) if M[i][k] == 1)
      for k in range(j-1,j-dist,-1):
        if M[i][k] == 0: break
        left.add((i,k))
        dist_left = j - k
      if dist_left == 0: continue
      dist = min(dist, dist_left)

      #right = set((i,k) for k in range(j+1,n) if M[i][k] == 1)
      for k in range(j+1,j+dist):
        if M[i][k] == 0: break
        right.add((i,k))
        dist_right = k - j
      if dist_right == 0: continue
      dist = min(dist, dist_right)

      # keep only the min distance in all directions because the + has to extend equally in all directions
      dist = min(len(up), len(down), len(left), len(right))
      #print "i,j,up", i, j, up
      #print "i,j,down", i, j, down
      if dist == 0: continue
      for x in up,down,left,right: 
        map(Plus.add, (y for y in list(x)[:dist]))
      print "dist, i, j, Plus", dist, i, j, Plus  
  BigPlus.add(frozenset(Plus))
        
#now BigPlus contains sets - each set is either a single cell or a list of tuples  of cells in a plus
#get the largest set of these
BigPlusMax = set()
count = 0
while True:
  found = True
  mx = list(BigPlus)[0]
  for x in list(BigPlus)[1:]:
    if (len(x) > len(mx)):
      mx = x
  BigPlusMax.add(frozenset(mx))
#check if it overlaps with any of the others  
  BigPlus.remove(frozenset(mx))
  for x in BigPlus:
    if mx.issubset(x): continue
    if not mx.isdisjoint(x):
      print "%s overlaps with %s" %(mx, x)
      found = False
      BigPlusMax.remove(frozenset(mx))
      break 
  if found:
    count += 1
    print "found %d sets" %(count)
    if count == 2 : break

print BigPlusMax
