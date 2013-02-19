#!usr/bin/env python
import glob,os

final_file = "results4.xyz"
outfile = open(final_file,"w")
nfiles = len(glob.glob("results_*.xyz"))
print "Merging resultfiles ..."

for i in range(nfiles):
	print(i)
	filename = "results_%03d.xyz"%i
	infile = open(filename,"r")
	tmp = infile.read()
	outfile.write(tmp)
	infile.close()
	os.remove(filename)
	

outfile.close()
print "done! All results now in file %s"%final_file
