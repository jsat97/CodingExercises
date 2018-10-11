#!/usr/bin/python

import sys


def is_palindrome(s):
  #print "s = ", s
  return (s == s[::-1])

def get_index_to_remove(s):
  length = len(s)
  for i in range(length/2):
    if (s[i] != s[-1 -i]):
      if i == 0:
        s1 = s[1:]
      else:
        s1 = s[:i] + s[i +1:]
      if is_palindrome(s1):
        return i
      else:
        if i == 0:
          s1 = s[:-1] 
        else:
          s1 = s[:-1 -i] + s[-i:]
        if is_palindrome(s1):
          return length -i -1 
  return -1
  

t = int(raw_input().strip())

for tno in range(t):
  s = raw_input().strip()
  index = -1
  if not is_palindrome(s):
    index = get_index_to_remove(s)

  print index

