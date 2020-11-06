from numpy import c_

import numpy as np
import matplotlib.pyplot as plt
import random
import math
x, y,z = np.loadtxt("resultat_4*4.txt",unpack=True)
m=[]
s=[]
for i in range (0,len(z)):

    for j in range(0,int(z[i])):
        m.append(x[i])
        s.append(y[i])
x_min = np.min(m)
x_max = np.max(m)

y_min = np.min(s)
y_max = np.max(s)

x_bins = np.linspace(x_min,x_max)
y_bins = np.linspace(y_min,y_max)

plt.hist2d(m,s,cmap='Reds')

plt.colorbar()

plt.title("How to plot a 2d histogram with matplotlib ?")

plt.savefig("histogram_2d_03.png", bbox_inches='tight')
plt.show()
plt.close()