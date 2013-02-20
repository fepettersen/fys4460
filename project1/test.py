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
yolo /= new.nparticles
print yolo.mean()/yolo.std()
fig1 = plt.figure()
a1 = fig1.add_subplot(111)
a1.plot(range(start,stop),yolo)
a1.set_xlabel('timestep number')
a1.set_ylabel('energy')


fig2 = plt.figure()
a2 = fig2.add_subplot(111)
a2.plot(range(start,stop),rofl)
a2.set_xlabel('timestep number')
a2.set_ylabel('temperature')


vec = new.DiffusionConstant("total_movement_.txt")

fig3 = plt.figure()
a3 = fig3.add_subplot(111)
a3.plot(range(len(vec)),vec)
a3.set_xlabel('timestep number')
a3.set_ylabel('mean square r(t)-r_0')

plt.show()