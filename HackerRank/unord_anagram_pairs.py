#!/usr/bin/python

import sys
import itertools
import collections

#l =  map(list,itertools.combinations(s, i))		#get list of sets with 1 element (i=1), 2 (i=2), 3 etc. in each loop

def consecutive_list(s, n):
  l = []
  for i in range(len(s) - (n-1)):
    l.append(s[i:i+n])
  return l

t = int(raw_input().strip())
compare = lambda x, y: collections.Counter(x) == collections.Counter(y)
a = []
b = []

for tno in range(t):
  anagram_pairs = 0
  s = raw_input().strip()
  for i in range(1,len(s)+1):
    l = consecutive_list(s, i)
    print "l", l
    j = -1
    while True:
			j += 1
			length = len(l)
			print "length, j", length, j
			if not length: break
			if j == length -1: break
			for k in range(j+1, length):
				print "k", k
				a, b = l[j], l[k]
				anagram_pair_bool = compare(a,b)
				print "l[j] l[k] pairs ?", a, b, anagram_pair_bool 
				if anagram_pair_bool:
					anagram_pairs += 1		
					l.remove(a)
					l.remove(b)
					j = -1
					break	

  print anagram_pairs 
