#!usr/bin/env python
import glob,os

outfile = open("results.xyz","w")
nfiles = len(glob.glob("results_*.xyz"))

for i in range(nfiles):
	infile = open("results_%03d.xyz"%i,"r")
	tmp = infile.read()
	outfile.write(tmp)
	print i
	infile.close()
	#os.remove(infile)

outfile.close()