#!/usr/bin/python
import sys

if __name__=="__main__":
	f=open(sys.argv[2], "rb+")
	f2=open(sys.argv[1], "rb")
	c=f2.read()
	if len(c) > 446:
		print "boot file " + sys.argv[1] + " too big"
	else:
		f.seek(0)
		f.write(c)
	f.close()
	f2.close()

