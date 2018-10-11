#!/usr/bin/python
import sys


one_to_twenty = {0:"", 1:"one", 2:"two", 3:"three", 4:"four", 5:"five", 6:"six", 7:"seven", 8:"eight", 9:"nine", 10:"ten", 11:"eleven", 12:"twleve", 13:"thirteen",
14:"fourteen", 15:"fifteen", 16:"sixteen", 17:"seventeen", 18:"eighteen", 19:"nineteen"}
tens= {10:"ten", 20:"twenty", 30:"thirty", 40:"forty", 50:"fifty", 60:"sixty", 70:"seventy", 80:"eighty", 90:"nintety"}

def mins_to_words(mins):
	if (mins <= 19):
		return one_to_twenty[mins] + " " + "minutes"
	else:
		no_tens = mins/10
		no_mins = mins%10
		if no_mins:
			s = tens[no_tens * 10] + " " + one_to_twenty[mins%10] + " " + "minutes"
		else:
			s = tens[no_tens * 10] + " minutes"
		return s


hrs = int(raw_input().strip())
mins = int(raw_input().strip())
if mins < 30:
	if mins == 0:
		print one_to_twenty[hrs] + " o' clock"
	elif mins == 15:
		print "quarter past " + one_to_twenty[hrs] 
	else:
		print mins_to_words(mins) + " past " + one_to_twenty[hrs] 
elif mins == 30:
	print "half past " + one_to_twenty[hrs] 
else:
	mins_to_the_hr = 60 - mins
	next_hr = hrs +1 if hrs < 12 else 1
	if mins_to_the_hr  == 15:
		print "quarter to " + one_to_twenty[next_hr]
	else:
		print mins_to_words(mins_to_the_hr) + " to " + one_to_twenty[next_hr]
