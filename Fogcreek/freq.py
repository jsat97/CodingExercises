#!/usr/bin/python
"""
solve problem on Fog Creek website
Jai 9-11-15 (jai_97@rediffmail.com)
./freq.py < <input file> 
the input file (inp) must be present in the current dir
Note: no error checking at present
"""
import sys

string="abcdefghijklmnopqrstuvwxyz_"
buf = sys.stdin.read()
buf=buf.replace('\n','')
freq={}
for i in string:
	freq[i] = buf.count(i)
answer=""
for c in sorted(freq, key=freq.get, reverse=True):			
	answer+=c	
print answer.split('_')[0]
