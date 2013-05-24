from data import *
import matplotlib.pyplot as plt
import numpy,sys

infile  = sys.argv[1] if len(sys.argv)>1 else "results.bin"
step = 15*400
infile = "velocityProfile_step%d.bin"%step

#new = Data(infile)

start = 0
#stop = new.ntimesteps
print "Timestep number %d"%step
print"-------------------"
tmp = open(infile,"rb")
res = tmp.readlines()
rz = []
vz = []

tmp.close()
length = 33.6/2.
zone = 5.72/2.

for line in res:
	tmp  =line.split()
	ry = float(tmp[1])
	rx = float(tmp[0])
	r = numpy.sqrt((rx-length)*(rx-length) + (ry-length)*(ry-length))
	rz.append(r)
	vz.append(float(tmp[-1]))


bin = numpy.linspace(0,max(rz),50);
r = numpy.zeros(len(bin))
counter = numpy.zeros(len(bin))
for i in xrange(len(rz)-1):
	for k in xrange(len(bin)):
		a = 0
		if (rz[i]-bin[k])>0 and (rz[i]-bin[k+1])<0:
			r[k] += abs(vz[i])
			counter[k] += 1
			a += 1
		if a>1:
			print k,a

print r,counter, sum(counter), len(res)
for k in xrange(len(bin)):
	r[k] /= counter[k]

#mpl.hist(vz,50)
#mpl.hist(r,50,color='grey')
mpl.plot(bin,r)
#mpl.plot(numpy.log(rz),numpy.log(numpy.abs(vz)),'o')
#print fig
mpl.xlabel("r_xy")
mpl.ylabel("mean(abs(v_z))")
mpl.title("velocity distribution at timestep #%d"%step)
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

