from data import *
import matplotlib.pyplot as plt

new = Data("results3.xyz")

yolo = []
rofl = []

start = 0
stop = 600

for i in xrange(start,stop):
	yolo.append(new.energy(i)/new.nparticles)
	rofl.append(new.temperature())
	print i

'''
fig1 = plt.figure()
a1 = fig1.add_subplot(111)
a1.plot(range(start,stop),yolo)
a1.set_xlabel('timestep number')
a1.set_ylabel('energy')

'''
fig2 = plt.figure()
a2 = fig2.add_subplot(111)
a2.plot(range(start,stop),rofl)
a2.set_xlabel('timestep number')
a2.set_ylabel('temperature')

plt.show()