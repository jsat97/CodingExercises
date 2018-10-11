#!/usr/bin/python
from itertools import islice
import tempfile, heapq

LINES_TO_READ = 10000         #lines to read before checking if MIN_INTERVAL is covered
MIN_INTERVAL = 300            #interval in secs for which events are sorted

def getkey(line):
  return line.split()[0]

def event_stream(filename):
  iters = read_log(filename, LINES_TO_READ)
  for i in heapq.merge(*iters):
    yield i

def read_sorted_file(file):
  for line in file:
    #print "read_sorted_file: ", line
    yield line

def read_log(file, n):
  count = 1
  with open(file) as f:
    iters = []
    done = False
    write_done = False
    sorted_line_list = []
    while True:
      lines = list(islice(f, n))
      if not lines: 
        done = True
        if write_done: 
          break
      else:
        sorted_line_list += sorted(lines, key=getkey)
        tmin = float(sorted_line_list[0].split()[0])
        tmax = float(sorted_line_list[-1].split()[0])
        delta_t = tmax - tmin
        #print "delta_t  =", delta_t 
      if delta_t >= MIN_INTERVAL or done:
        #print "creating tempfile %d" %(count)
        count += 1
        f_temp = tempfile.TemporaryFile()
        f_temp.write("".join(sorted_line_list))
        f_temp.seek(0)
        iters.append(read_sorted_file(f_temp))
        write_done = True
        sorted_line_list = []
      else:
        write_done = False
      if done: break  
  f.close()
  return iters


for event in event_stream("log.out.2"):
  #update_model(event)
  print event,
