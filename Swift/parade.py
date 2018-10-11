#!/usr/bin/python
import sys

# https://swiftstack.com/i-love-a-parade/
# version 0.1 23/1/2016
# Jai <jai_97@rediffmail.com> 
#
def make_parade_list(cntry_pairs):
  global check_order_again
  global parade_list
  for c1,c2 in cntry_pairs:       #c1 before c2 always
    if c1 not in parade_list:
      if c2 not in parade_list:     # both absent
        parade_list.insert(indx, c2)
        parade_list.insert(parade_list.index(c2), c1)
      else:    #c1 not present, c2 present 
        parade_list.insert(parade_list.index(c2), c1)
    else: 
      if c2 not in parade_list:   #c1 present, c2 not present - insert at 0 for both cases
        if parade_list.index(c1) == len(parade_list) -1:
          parade_list.append(c2)
        else:
          parade_list.insert(parade_list.index(c1)+1, c2)
     
      else:   #both present - if already in order, nothing to do. else need to check and reorder
        if parade_list.index(c1) > parade_list.index(c2):   # c2 is before c1
          if [c2,c1] in cntry_pairs:      #explicit rule c2 before c1 ?
            print "Invalid. %s before %s conflicts with %s" %(c1, c2, [c2, c1])
            return -1
          # there could be an implicit rule which forbids [c1,c2]
          # if we put c1 before  c2 in -> a b c c2 d e c1 f g
          # -> a b c c1 c2 d e f g
          # everything to the left of c2 (a,b,c) is still to the left of c2
          # everything to the right of c1 (f,g) is still to the right of c1
          # right of c2 but left of c1 (d,e) - were to the left of c1, but now, they are to the right. so, if there is a rule for (d,e) before c1,
          # it conflicts with having c1 before c2
          # find out the countries after c2 -> (c2,x), (c2,y) ...
          # if they are also before c1 -> (x,c1) ..
          # there s a conflict
          #
          after_c2_pairs = [i for i in cntry_pairs if i[0] == c2]
          #print "after_c2 _pairs", after_c2_pairs
          if len(after_c2_pairs): 
            after_c2_before_c1_pairs = \
            [cntry_pair for cntry_pair in cntry_pairs  \
            for after_c2_pair in after_c2_pairs  \
            if cntry_pair[1] == c1 and after_c2_pair[1] == cntry_pair[0] ]
            #print "after_c2_before_c1_pairs ", after_c2_before_c1_pairs
            if len(after_c2_before_c1_pairs): 
              print "Invalid. %s before %s conflicts with %s" %(c1, c2, after_c2_before_c1_pairs) 
              return -1 
           
          # should be ok to move c1 to before c2 
          #print "moving %s to before %s" %(c1, c2)
          parade_list.remove(c1)
          parade_list.insert(parade_list.index(c2), c1)
          check_order_again = True 
          return 0
        else:
          #print "%s is already before %s" %(c1, c2)
          pass
  return 0

indx = 0
error = False
cntry_pairs = []
parade_list=[]
for line in sys.stdin:
  #print line,
  if line.strip()[0] == '#': continue
  line_list = line.strip().split()
  i = line_list.index("comes")
  c1 = " ".join(line_list[0:i])
  i += 1
  pos = line_list[i]
  assert(pos == "before" or pos == "after")
  i += 1
  c2 = " ".join(line_list[i:])

  if pos == "before":
    cntry_pairs.append([c1,c2])
  else:
    cntry_pairs.append([c2,c1])

#print "cntry_pairs ", cntry_pairs 
while True:
  check_order_again = False
  error = make_parade_list(cntry_pairs)
  #print parade_list
  if error == -1:
    #print "Invalid" 
    break
  elif not check_order_again:
    for i in parade_list: print i
    break
