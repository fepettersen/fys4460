from data import *
import matplotlib.pyplot as plt
import numpy,sys

infile  = sys.argv[1] if len(sys.argv)>1 else "results.xyz"

new = Data(infile)

start = 0
stop = new.ntimesteps


yolo = numpy.zeros(stop-start)
rofl = numpy.zeros(stop-start)
#swag = numpy.zeros(stop-start)
'''
for i in xrange(start,stop):
	yolo[i] = new.energy(i)
	rofl[i] = new.temperature()
	print i


#print yolo.mean()/yolo.std()

fig1,a1 = new.makeplot(yolo,y_label="energy")
fig2,a2 = new.makeplot(rofl,y_label = "temperature")

something = 0
for i in xrange(start,stop):
	something = new.energy(i)
	yolo[i] = new.E_k
	rofl[i] = new.U_tot

fig1,a1 = new.makeplot(yolo,y_label = "kinetic energy")
fig2,a2 = new.makeplot(rofl,y_label = "potential energy")
'''


new.radial_distribution(260,330,61)
'''
vec,pressure = new.DiffusionConstant(\
	"total_movement_.txt")
fig3,a3 = new.makeplot(vec, y_label = "mean square stuff")
volume = (5.260/3.405)*16
rho = new.nparticles/volume
pressure /= (3*volume)
#new.getResults(0)
#fig,a = new.make_histogram(new.v[:,0],x_label = \
#	"velocity distribution in x direction")
pressure += rho*rofl
fig3,a3 = new.makeplot(pressure[100:],other = rofl[100:], \
	y_label = "pressure",x_label = "temperature")

#Put in class!!!

#resultfiles/total_movement_ncells16_T300K_therm.txt
plt.show()'''