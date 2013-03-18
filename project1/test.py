from data import *
import matplotlib.pyplot as plt
import numpy,sys

infile  = sys.argv[1] if len(sys.argv)>1 else "results.bin"

new = Data(infile)

start = 0
stop = new.ntimesteps





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
infilename = "MD_results_atoms%d_timesteps%d_.txt"\
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
