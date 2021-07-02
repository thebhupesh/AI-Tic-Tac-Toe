import matplotlib.pyplot as plt
import numpy as np
  
X, Y = np.loadtxt('output1.3.txt', delimiter=' ', unpack=True)
A, B = np.loadtxt('output2.3.txt', delimiter=' ', unpack=True)  
plt.plot(X, Y, color='r', label='Only Min-Max')
plt.plot(A, B, color='g', label='Proposed Algorithm')
plt.title('Time Complexcity of Test 3')
plt.xlabel('Game No.')
plt.ylabel('Time in seconds')
plt.legend()
plt.ylim(0,0.15)
plt.xlim(0,30)
plt.show()
