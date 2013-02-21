import numpy as np
import matplotlib.pyplot as mpl
class Data():
	def __init__(self,resultfile):

		infile = open(resultfile,"r")
		self.tmp = infile.readlines()
		infile.close()
		self.nparticles = int(self.tmp[0])
		self.ntimesteps = len(self.tmp)/(self.nparticles+2)
		self.E_k = 0
		self.U_tot = 0
		self.mean = [0 for i in range(4)]
		self.std = [0 for i in range(4)]
		self.v = np.zeros((self.nparticles,3))
		self.r = np.zeros((self.nparticles,3))
		

	def getResults(self,timestep_no):
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

	def stats(self,x=False,y=False,z=False,all=False):
		xx = 0

		if(x):
			#makeplot_x()
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

	def makeplot(self,vector, y_label= "",x_label = "timestep number"):
		fig3 = mpl.figure()
		a3 = fig3.add_subplot(111)
		a3.plot(range(len(vector)),vector)
		a3.set_xlabel(x_label)
		a3.set_ylabel(y_label)
		return fig3, a3
