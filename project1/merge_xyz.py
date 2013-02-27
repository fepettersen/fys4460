#!usr/bin/env python
import glob,os,sys

final = "results.xyz"
final_file = sys.argv[1] if len(sys.argv) > 1 else final
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
