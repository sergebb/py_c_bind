import numpy as np
import scipy as sp
import corr
import time

def ccf(data):
    return np.array([sp.correlate(p, np.concatenate((p,p))) for p in data])

z = np.zeros(1000000).reshape(1000,1000)
for i in range(1000):
    for j in range(1000):
        z[i,j]=i^j

#z = np.array([[2.0,3.0,1.0,4.0,1.3,4.5,6.4,7.6]])

#print 2,libcorr.square(2)
# print z
x = np.array(z,dtype=np.float32)

start = time.time()     #Numpy
z = ccf(x)
numpy_time = time.time()- start

y=x                     #Cpp
start = time.time()
corr.corr(y)
cpp_time = time.time()- start
print "Numpy - %(numpy_time)f \nCpp - %(cpp_time)f" % locals()
#print x
# print z
# print y
