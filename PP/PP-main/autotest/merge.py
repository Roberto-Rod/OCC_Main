
from __future__ import print_function


import getopt 
import sys
import codecs
import re


msg = "sss"

def printHelp() :
	print ("Paramaters are ")
	print (" -f inputfile   ")
	print (" -m merge file ")
	print ("Output is to the standard output")

try:
	opts, args = getopt.getopt(sys.argv[1:], 'f:m:')
except getopt.error, msg:
     #sys.stdout = sys.stderr
     print (msg)
     #print (__doc__%globals() )
     printHelp()
     sys.exit(2)


inputfile = ""
mergefile = ""
debugdump = 0
extra = 0


for o, a in opts:
      if o == '-f':
         inputfile = a
      if o == '-m':
         mergefile = a


lines = open( inputfile, "r" ).readlines()

mergelines = open( mergefile, "r" ).readlines()


lineoffset = 0 
numberlines = 0

currentline = 0 
printlines = len( lines ) 

mergecount = 0 

# print ( mergelines )

for mergeline in mergelines:

    if mergecount > 0:
         print ( mergeline, end='' )
	 #print ( mergecount )
	 mergecount -= 1 
    else:
	# print ( mergeline[0] )
        mergeline1 = mergeline[1:] 
	if mergeline[0] != 'a' :
		print (mergeline)
		print ("Error: Only the additions of lines is allowed")
		print ("Changing or deleting is not allowed")
		print ("A section can be commented out and add a new section")
		exit(1)


        words = mergeline1.split()

        lineoffset = int(words[0])
	mergecount = int(words[1])

	#print ( "Debug:")
	#print ( lineoffset)
	#print ( mergecount )
        while currentline < lineoffset :
	     print ( lines[currentline], end='')
             currentline += 1

        #print ( lineoffset )
        #print ( words )
	# Not finish off the end o 


#print ( "Debug:" )
#print ( printlines )
while currentline < printlines:
	print ( lines[currentline], end='')
        currentline += 1

exit(1) 


