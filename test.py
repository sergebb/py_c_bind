
import numpy as np
import scipy as sp
import corr


def ccf(data):
    return np.array([sp.correlate(p, np.concatenate((p,p))) for p in data])


    

z = np.zeros(1000000).reshape(1000,1000)
for i in range(1000):
	for j in range(1000):
		z[i,j]=i^j

#z = np.array([[2.0,3.0,1.0,4.0,1.3,4.5,6.4,7.6]])

#print 2,libcorr.square(2)
print z
x = np.array(z,dtype=np.float32)
z = ccf(x)
corr.corr(x)
#print x
print z
