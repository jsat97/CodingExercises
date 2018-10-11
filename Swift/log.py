#!/usr/bin/python
import time
import random

JITTER = 275 
TICKS = 10000
LINES_PER_TICK = 1000

def log_line(now):
	timestamp = now - (random.random() * JITTER)
	return "%f   City %d" % (timestamp, random.randint(0,10000))


start = time.time()
for tick in xrange(TICKS):
	now = start + tick
	for num_line in xrange(LINES_PER_TICK):
		print(log_line(now))
