#!/usr/bin/python
import sys

#count the bits that OR to 1 in the 2 lists 
def CountBitArrayOR(arr1, arr2, length):
	count =0
	#for i in range(length):
	#	count += int(arr1[i]) | int(arr2[i])
	val = int(arr1, 2) | int(arr2, 2)
	count = bin(val).count('1')
	#while (val):
	#	count += val & 1
	#	val = val >> 1
	return count
		

n,m = raw_input().strip().split(' ')
n,m = [int(n),int(m)]
topic = []
topic_i = 0
topic_bit_val = []
for topic_i in xrange(n):
	topic_t = str(raw_input().strip())
	topic.append(topic_t)
	#print topic_bit_val[topic_i] 

overlap_max_pairs = []	
overlap_max = 0
for i in xrange(n -1):
	for j in xrange(i +1, n):
		overlap_count = CountBitArrayOR(topic[i], topic[j], m)
		overlap_max = max(overlap_max, overlap_count)		
		#print "overlap_count overlap_max i j ", overlap_count, overlap_max, i, j 
		overlap_max_pairs.append(overlap_count) 

print overlap_max
print overlap_max_pairs.count(overlap_max)
