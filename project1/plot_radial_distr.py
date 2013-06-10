import numpy as np
import matplotlib.pyplot as mpl

infile = np.loadtxt('radial_distr.txt')
mpl.plot(infile[0:-2,1],infile[0:-2,0])
mpl.show()
