from data import *
import matplotlib.pyplot as plt
import numpy,sys

infile  = sys.argv[1] if len(sys.argv)>1 else "results.bin"
infile = "velocityProfile_step2400.bin"

#new = Data(infile)

start = 0
#stop = new.ntimesteps

tmp = open(infile,"rb")
res = tmp.readlines()
rx = []
vz = []
tmp.close()
length = 33.6/2.
zone = 5.72/2.

for line in res:
	tmp  =line.split()
	ry = float(tmp[1])
	rz = float(tmp[2])
	if abs(ry-length)<zone and abs(rz-length)<zone:
		rx.append(float(tmp[0]))
		vz.append(float(tmp[-1]))
b = min(rx)
for i in xrange(len(rx)):
	rx[i] -=  b
#mpl.hist(vz,50)
#mpl.hist(rx,50,color='grey')
mpl.plot(rx,vz,'o')
mpl.show()
#print yolo.mean()/yolo.std()


'''
something = 0
for i in xrange(start,stop):
	something = new.energy(i)
	yolo[i] = new.E_k
	rofl[i] = new.U_tot

fig1,a1 = new.makeplot(yolo,y_label = "kinetic energy")
fig2,a2 = new.makeplot(rofl,y_label = "potential energy")

'''
#new.ClaculateEnergy()
#new.radial_distribution(26,70,61)
'''
infilename = "MD_results_atoms%d_timesteps%d.txt"\
%(new.nparticles,new.ntimesteps)
new.DiffusionConstant(infilename)
fig3,a3 = new.makeplot(new.meanr2, y_label = "mean square stuff")
#volume = (5.72/3.405)*20
#rho = new.nparticles/volume
#pressure /= (3*volume)
#new.getResults(0)
#fig,a = new.make_histogram(new.v[:,0],x_label = \
#	"velocity distribution in x direction")
#pressure += rho*rofl
#fig3,a3 = new.makeplot(pressure[100:],other = rofl[100:], \
#	y_label = "pressure",x_label = "temperature")

plt.show()
'''