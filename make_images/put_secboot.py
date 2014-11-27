#!/usr/bin/python
import sys

if __name__=="__main__":
	f=open(sys.argv[2], "rb+")
	f2=open(sys.argv[1], "rb")
	c=f2.read()
	f.seek(512)
	f.write(c)
	f.close()
	f2.close()


