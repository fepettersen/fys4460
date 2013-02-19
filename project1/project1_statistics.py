import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab

makeplot = False
x_plot = False
y_plot = False
z_plot = False
norm_plot = False

resultfile = "results3.xyz"
timestep_no = 200;

#read file
infile = open(resultfile,"r")
tmp = infile.readlines()
infile.close()

nparticles = float(tmp[0])
xyz = np.zeros((nparticles,3))
r = np.zeros((nparticles,3))

counter = 0
i= int(timestep_no*nparticles +2*(timestep_no+1))
while counter<nparticles:
	dummy = tmp[i].split()[4:]
	dummy2 = tmp[i].split()[1:4]
	for j in xrange(3):
		xyz[counter,j] = float(dummy[j])
		r[counter,j] = float(dummy2[j])
	i += 1
	counter += 1

#Plotting
fig = plt.figure()
#v_x
if(x_plot):
	ax = fig.add_subplot(1,1,1)
	n, bins, patches = ax.hist(xyz[:,0], 50, normed=1, facecolor='black', alpha=0.75)
	ax.set_xlabel('velocity in x direction')
	ax.set_ylabel('Probability')
	ax.grid(True)

mean_x = xyz[:,0].mean()
std_x = xyz[:,0].std()

#v_y
if(y_plot):
	ay = fig.add_subplot(2,1,1)
	ny, binsy, patchesy = ay.hist(xyz[:,1], 50, normed=1, facecolor='grey', alpha=0.75)
	ay.set_xlabel('velocity in y direction')
	ay.set_ylabel('Probability')
	ay.grid(True)

mean_y = xyz[:,1].mean()
std_y = xyz[:,1].std()

#v_z
if(z_plot):
	az = fig.add_subplot(3,1,1)
	nz, binsz, patchesz = az.hist(xyz[:,2], 50, normed=1, facecolor='red', alpha=0.75)
	az.set_xlabel('velocity in z direction')
	az.set_ylabel('Probability')
	az.grid(True)

mean_z = xyz[:,2].mean()
std_z = xyz[:,2].std()

ball = np.zeros(len(xyz))
for i in range(len(xyz)):
	ball[i] = np.sqrt(xyz[i,0]*xyz[i,0]+xyz[i,1]*xyz[i,1]+xyz[i,2]*xyz[i,2])

#norm(v)
if(norm_plot):
	a = fig.add_subplot(1,1,1)
	nall, binsall, patchesall = a.hist(ball, 50, normed=1, facecolor='green', alpha=0.75)
	a.set_xlabel('speed')
	a.set_ylabel('Probability')
	a.grid(True)

mean_all = ball.mean()
std_all = ball.std()

print("At timestep number %d "%timestep_no)
print("mean v_x = %g  standard deviation: %g "%(mean_x,std_x))
print("mean v_y = %g  standard deviation: %g "%(mean_y,std_y))
print("mean v_z = %g  standard deviation: %g "%(mean_z,std_z))
print("mean speed = %g  standard deviation: %g "%(mean_all,std_all))

if(makeplot):
	plt.show()
#--------------------------------------------------------------
#------Energy

def U(r):
	r2 = np.dot(r,r)
	return 4*(1/(r2**6) - 1/(r2**3))

def Kinetic(v):
	return 0.5*np.dot(v,v)
U_tot = 0
E_k = 0
for i in xrange(len(r)):
	U_tot += U(r[i,:])
	E_k += Kinetic(xyz[i,:])

Energy = U_tot+E_k
print("The total energy is %g"%Energy)