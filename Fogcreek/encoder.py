#!/usr/bin/python
import random
import sys

def word_has_unique_letters(word):
	unique=False
	if (len(word) <= 1):
		return True
	else:
		l=list(word)
		l=sorted(l)
		old=l[0]
		for i in l[1:]:
			#print i, old
			if (i == old):
				return False	
			old=i
	return True

def find_word(max_words, max_len):
	f=open("/usr/share/dict/words", "r")
	count=0
	words=[]
	while(True):
		word=f.readline().lower()
		word=word.strip('\n')
		unique = word_has_unique_letters(word)
		if (unique):
			if (len(word) == max_len):
				#print ("%s %d %d" %(word,len(word),max_len))
				words.append(word)
				count+=1
				if (count == max_words):
					return words	
			
def main(argv):
	if (len(sys.argv) != 3):
		print ("%s <# of words> <word len>\n" %(sys.argv[0]))
		sys.exit(1)

	max_words=int(sys.argv[1])
	max_len = int(sys.argv[2])

	#word=find_word(1, 15)[0]
	word=find_word(max_words, max_len)[0]
	print >> sys.stderr, "encoding word -->", word
	freq=[]
	for i in range(0,len(word)):
		ran = random.randrange(1,100)
		while(ran in freq):
			ran = random.randrange(1,100)
		freq.append(ran)
	freq=sorted(freq, reverse=True)
	#print freq

	buf=[]
	for i in range(0,len(freq)):
		for j in range(0,freq[i]):
			buf.append(word[i])

	random.shuffle(buf)
	buf1="".join(buf)
	print buf1

if __name__ == "__main__":
	main(sys.argv)
