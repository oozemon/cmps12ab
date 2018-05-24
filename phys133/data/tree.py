import numpy
#from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

f=open ("Ba-133 DOPE.TKA",'r')
#print f.read()

x=[0]*1024
i=0
while i<1024:
		x[i]=i
		i=i+1
		
#print(x)



data = numpy.genfromtxt('Ba-133 DOPE.TKA', delimiter='\n')

plt.bar(x[0:500], data[0:500])
plt.xlabel('Bin #')
plt.ylabel('Counts')
plt.grid(True)

plt.show()
