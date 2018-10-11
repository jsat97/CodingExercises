#!/usr/bin/python
import sys
from collections import Counter as mset

s1 = raw_input().strip()
s2 = raw_input().strip()
common = mset(s1) & mset(s2)
#contains common non -unique elements
common_list = list(common.elements())
#print common_list

len_common = len(common_list)
deletions = len(s1) - len_common + len(s2) - len_common
print deletions 
