#!/usr/bin/python
from itertools import islice
import tempfile, heapq

LINES_TO_READ = 300000 

def getkey(line):
  return float(line.split()[0])

def event_stream(filename):
  iters = read_log(filename, LINES_TO_READ)
  return heapq.merge(*iters)

def read_sorted_file(file):
  for line in file:
    #print "read_sorted_file: ", line
    yield line

def read_log(file, n):
  count = 0
  with open(file) as f:
    iters = []
    sorted_line_list = []
    while True:
      lines = list(islice(f, n))
      if not lines: 
        break
      else:
        sorted_line_list = sorted(lines, key=getkey)
        #print "creating tempfile %d" %(count)
        count += 1
        f_temp = tempfile.TemporaryFile()
        #f_temp = open("/tmp/junk_%d" %(count), "w+")
        f_temp.write("".join(sorted_line_list))
        f_temp.seek(0)
        iters.append(read_sorted_file(f_temp))
  f.close()
  return iters

for event in event_stream("log.out.3"):
  #update_model(event)
  print event,
