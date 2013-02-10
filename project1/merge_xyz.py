#!usr/bin/env python
import glob,os

outfile = open("results.xyz","w")
nfiles = len(glob.glob("results_*.xyz"))

for i in range(nfiles):
	filename = "results_%03d.xyz"%i
	infile = open(filename,"r")
	tmp = infile.read()
	outfile.write(tmp)
	print i
	infile.close()
	os.remove(filename)

outfile.close()