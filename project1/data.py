import numpy as np
class Data():
	def __init__(self,resultfile):

		infile = open(resultfile,"r")
		self.tmp = infile.readlines()
		infile.close()
		self.nparticles = int(self.tmp[0])
		self.ntimesteps = len(self.tmp)/self.nparticles
		self.E_k = 0
		self.mean = [0 for i in range(4)]
		self.std = [0 for i in range(4)]
		self.v = np.zeros((self.nparticles,3))
		self.r = np.zeros((self.nparticles,3))
		

	def getResults(self,timestep_no):
		counter = 0
		i= int(timestep_no*self.nparticles +2*(timestep_no+1))
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
			#plot
			print("hei")

		for j in range(len(self.mean)-1):
			self.mean[j] = self.v[:,j].mean()
			self.std[j] = self.v[:,j].std()

		ball = np.zeros(len(self.nparticles))
		for i in xrange(len(self.nparticles)):
			ball[i] = np.linalg.norm(self.v[i,:],2)
		mean[3] = ball.mean()
		std[3] = ball.std()
		return mean,std

	def energy(self,timestep_no):
		self.getResults(timestep_no)
		kin_en = 0
		pot_en = 0
		def U(r):
			r2 = np.dot(r,r)
			return 4*(1/(r2**6) - 1/(r2**3))

		def Kinetic(v):
			return 0.5*np.dot(v,v)
		U_tot = 0
		
		for i in xrange(self.nparticles):
			pot_en += U(self.r[i,:])
			kin_en += Kinetic(self.v[i,:])

		self.E_k = kin_en
		U_tot = pot_en
		Energy = U_tot+self.E_k
		return Energy

	def temperature(self):
		return 2*self.E_k/(3*self.nparticles)
