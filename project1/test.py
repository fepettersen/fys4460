from data import *
import matplotlib.pyplot as plt
import numpy

new = Data("results4.xyz")

start = 0
stop = new.ntimesteps


yolo = numpy.zeros(stop-start)
rofl = numpy.zeros(stop-start)
#swag = numpy.zeros(stop-start)

for i in xrange(start,stop):
	yolo[i] = new.energy(i)
	rofl[i] = new.temperature()
	print i


#print yolo.mean()/yolo.std()

fig1,a1 = new.makeplot(yolo,y_label="energy")
fig2,a2 = new.makeplot(rofl,y_label = "temperature")
'''
something = 0
for i in xrange(start,stop):
	something = new.energy(i)
	yolo[i] = new.E_k
	rofl[i] = new.U_tot

fig1,a1 = new.makeplot(yolo,y_label = "kinetic energy")
fig2,a2 = new.makeplot(rofl,y_label = "potential energy")
'''
vec,pressure = new.DiffusionConstant("total_movement_.txt")
fig3,a3 = new.makeplot(pressure, y_label = "pressure")
#Put in class!!!
volume = (5.260/3.405)*16
rho = new.nparticles/volume
pressure /= (3*volume)
pressure += rho*rofl



plt.show()