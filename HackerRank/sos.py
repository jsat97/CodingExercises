#!/usr/bin/python
import sys


S = raw_input().strip()
len = len(S)
changed = 0
for i in range(0,len,3):
  s = S[i:i+3]
#  print s
  changed += 3 -(s[0].count('S') + s[1].count('O') + s[2].count('S') )
print changed
