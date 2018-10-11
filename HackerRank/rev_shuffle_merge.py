#!/usr/bin/python

import sys
import string

s = raw_input().strip()
dict = {k:0 for k in string.ascii_lowercase}
for i in string.ascii_lowercase:
	dict[i] = s.count(i)

#print dict
d1 = {i:dict[i] for i in string.ascii_lowercase if dict[i]}
d2 = {i:dict[i]/2  for i in d1.keys()}

#print "d1 = ", d1
print "d2 = ", d2

r = s[::-1]

d3 = {i:0 for i in d1.keys()}
d4 = {i:0 for i in d1.keys()}

min_lex = 'z'
out = ""
for i in r:
  min_lex = min(i, min_lex)
  left = d1[i] - d3[i]
  if d2[i] == left and not d4[i]:
    out += i
    d4[i] += 1    #picked this
  else:
    out += min_lex
  d3[i] += 1      #count the no of times we pass each letter

  print "i min_lex count d2 left out", i, min_lex, d3[i], d2[i], left, out
#print "d3 = ", d3
#print out
