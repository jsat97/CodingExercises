#!/usr/bin/python

import heapq,sys, random, array

def getkey(item):
  return item[0]

def func1(n):
  a = []
  for i in xrange(1,n):
    a.append([random.randint(1,n), i])
  a = sorted(a, key=getkey)
  for x in a:
    yield(x)

def func2(n):
  a = []
  for i in xrange(1,n):
    a.append([random.randint(1,n), i])
  a = sorted(a, key=getkey)
  for x in a:
    yield(x)


gen = [func1(100), func2(200)]
for i in heapq.merge(*gen):
  print i

#for i in func1(100):
#  print i
