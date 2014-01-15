import libcorr
import numpy as np
import scipy as sp


def ccf(data):
    return np.array([sp.correlate(p, np.concatenate((p,p))) for p in data])

def corr(data):
    return libcorr.Correlate(data)
    

z = np.zeros(1000000).reshape(1000,1000)
for i in range(1000):
	for j in range(1000):
		z[i,j]=i^j

#z = np.array([[2.0,3.0,1.0,4.0,1.3,4.5,6.4,7.6]])

#print libcorr.greet()
#print 2,libcorr.square(2)
print z
x = np.array(z,dtype=float)
z = ccf(x)
y = corr(x)
#print x
print z
print y
