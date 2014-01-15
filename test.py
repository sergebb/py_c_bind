import libcorr
import numpy as np
import scipy as sp


def ccf(data):
    return np.array([sp.correlate(p, np.concatenate((p,p))) for p in data])

z = np.zeros(100).reshape(10,10)
for i in range(10):
	for j in range(10):
		z[i,j]=i^j

z = np.array([[2.0,3.0,1.0,4.0,1.3,4.5,6.4,7.6]])

print libcorr.greet()
print 2,libcorr.square(2)
print z
x = np.array(z,dtype=float)
x = libcorr.Correlate(x)
y = ccf(z)
print x
print z
print y
