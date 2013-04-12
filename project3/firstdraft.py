from pylab import *
from scipy.ndimage import measurements
L = 100
r = rand(L,L)
p = 0.6

z = r<p
imshow(z, origin='lower')
show()