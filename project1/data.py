import numpy as np
import matplotlib.pyplot as mpl
import os
class Data():
	def __init__(self,resultfile):

		extension = resultfile.split('.')[-1]
		if extension == 'dat':
			infile = open(resultfile,"rb")
		else:
			infile = open(resultfile,"r")

		self.nparticles = int(infile.readline())
		#length = os.stat(resultfile)
		dummy = infile.readline().split()
		steps = dummy[0]
		if steps == '0' or type(steps) == str:
			steps = int(raw_input("Please provide number of timesteps:  "))

		self.ntimesteps = steps
		print self.ntimesteps
		self.E_k = 0
		self.U_tot = 0
		self.mean = [0 for i in range(4)]
		self.std = [0 for i in range(4)]
		self.v = np.zeros((self.nparticles,3))
		self.r = np.zeros((self.nparticles,3))
		#tmp2 = self.tmp[3].split()[1:4]
		#tmp3 = self.tmp[4].split()[1:4]
		b = dummy[1]
		if type(b) != float:
			b = float(raw_input("Please provide the lattice constant b not divided by sigma! :  "))
			b /= 3.405
		self.b = b
		infile.close()
		if extension == 'dat':
			self.infile = open(resultfile,"rb")
		else:
			self.infile = open(resultfile,"r")
		

	def getResults(self,timestep_no):

		self.infile.readline()
		self.U_tot = float(self.infile.readline().split()[-1])
		for i in xrange(self.nparticles):
			tmp =self.infile.readline().split()
			dummy = tmp[4:]
			dummy2 = tmp[1:4]
			for j in xrange(3):
				self.v[i,j] = float(dummy[j])
				self.r[i,j] = float(dummy2[j])
		'''		
		counter = 0
		i= int(timestep_no*self.nparticles +2*(timestep_no+1))
		spoc = timestep_no*(self.nparticles+2)+1
		self.U_tot = float(self.tmp[spoc].split()[-1])#/self.nparticles
		while counter<self.nparticles:
			dummy = self.tmp[i].split()[4:]
			dummy2 = self.tmp[i].split()[1:4]
			for j in xrange(3):
				self.v[counter,j] = float(dummy[j])
				self.r[counter,j] = float(dummy2[j])
			i += 1
			counter += 1
		'''

	def stats(self,x=False,y=False,z=False,all=False):
		xx = 0

		if(x):
			#self.make_histogram(v[0,:],)
			xx+=1
		if(y):
			#makeplot_y()
			xx+=1
		if(z):
			#makeplot_z()
			xx+=1
		if(all):
			#makeplot_all()
			xx+=1
		if(xx!=0):
			#mpl.show()
			print("hei")

		for j in range(len(self.mean)-1):
			self.mean[j] = self.v[:,j].mean()
			self.std[j] = self.v[:,j].std()

		ball = np.zeros(self.nparticles)
		for i in xrange(self.nparticles):
			ball[i] = np.linalg.norm(self.v[i,:],2)

		self.mean[3] = ball.mean()
		self.std[3] = ball.std()

		return self.std[3], self.mean[3]

	def energy(self,timestep_no):
		self.getResults(timestep_no)
		kin_en = 0

		def Kinetic(v):
			return 0.5*np.dot(v,v)
		
		for i in xrange(self.nparticles):
			kin_en += Kinetic(self.v[i,:])

		self.E_k = kin_en#/self.nparticles
		Energy = self.U_tot+self.E_k
		return Energy

	def temperature(self):
		return 2*self.E_k/(3*self.nparticles)

	def DiffusionConstant(self,filename):
		results = np.loadtxt(filename)
		meanr2 = results[:,0]/self.nparticles
		pressure = results[:,1]
		return meanr2,pressure

	def makeplot(self,vector,other=None, y_label= "",x_label = "timestep number"):
		
		if other is not None:
			against = other 
		else:
			against = range(len(vector))

		fig3 = mpl.figure()
		a3 = fig3.add_subplot(111)
		a3.plot(against,vector)
		a3.set_xlabel(x_label)
		a3.set_ylabel(y_label)
		return fig3, a3

	def make_histogram(self,vector,x_label="",y_label="Probability"):
		fig = mpl.figure()
		a = fig.add_subplot(111)
		n, bins, patches = a.hist(vector, 50, normed=1, \
			facecolor='black', alpha=0.75)
		a.set_xlabel('velocity in x direction')
		a.set_ylabel('Probability')
		a.grid(True)
		return fig,a

	def radial_distribution(self,start,stop,n):
		r_max = 0.5*self.b*(self.nparticles/4)**(1/3.0)
		zones = np.linspace(0,r_max,n)
		print zones
		counter = np.zeros(n)
		for s in xrange(stop-start):
			self.getResults(start+s)
			for i in xrange(self.nparticles):
				r =np.linalg.norm(self.r[i,:],2)
				#r = self.r[i,0]
				for j in xrange(1,n,1):
					if (r-zones[j])<0 and (r-zones[j-1])>=0:
						counter[j-1]+=1
		counter /= (stop-start)
		print np.sum(counter), "  ", self.nparticles
		fig,a = self.makeplot(counter,zones,x_label="position",\
			y_label="number of particles")
		mpl.show()

	def ClaculateEnergy(self,start = 0, stop = None , makeplot = True):
		if(stop==None):
			stop = self.ntimesteps
		print("Caclulating energy...")
		yolo = np.zeros(stop-start)
		rofl = np.zeros(stop-start)
		step = int ((stop-start)/100)
		print step
		for i in xrange(start,stop):
			yolo[i] = self.energy(i)
			rofl[i] = self.temperature()
			print i
			if(i/step==0):
				print("%d percent done"%((i/step)*100))

		if(makeplot):
			fig1,a1 = self.makeplot(yolo,y_label="Energy")
			fig2,a2 = self.makeplot(rofl,y_label = "Temperature")
			mpl.show()
		else:
			return yolo,rofl