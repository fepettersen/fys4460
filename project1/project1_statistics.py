import math
import matplotlib.pyplot as plt

infile = open("test.xyz","r")
tmp = infile.readlines()
infile.close()
xyz = range(len(tmp))
i=0
#print xyz
for line in tmp:
	xyz[i] = line.split()[4:]
	i += 1

for k in range(len(xyz)-2):
	for j in range(3):
		xyz[k+2][j] = float(xyz[k+2][j])

def norm(vec):
	return math.sqrt(vec[0]*vec[0] +vec[1]*vec[1]+vec[2]*vec[2])

v = [norm(xyz[i+2]) for i in range(len(xyz)-2)]
plt.plot(sorted(v))
plt.show()