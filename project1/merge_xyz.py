#!usr/bin/env python
import glob,os,sys

final = "results.bin"
final_file = sys.argv[1] if len(sys.argv) > 1 else final
extension = final_file.split('.')[-1]
body = final_file.split('.')[0]
if extension != '.bin':
	final_file = body + '.bin'

outfile = open(final_file,"wb")
nfiles = len(glob.glob("results_*.bin"))
print "Merging resultfiles ..."

for i in range(nfiles):
	print(i)
	filename = "results_%04d.bin"%i
	infile = open(filename,"rb")
	tmp = infile.read()
	outfile.write(tmp)
	infile.close()
	os.remove(filename)
	

outfile.close()
print "done! All results now in file %s"%final_file
