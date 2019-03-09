# Import the necessary packages and modules
import matplotlib.pyplot as plt
import numpy as np

# Prepare the data
x = np.linspace(0, 10, 100)
y = np.linspace(2, 29, 200)

# Plot the data
plt.plot(x, x, label='linear')
plt.plot(y, y, label='linear')

# Add a legend
plt.legend()

# Show the plot
#plt.show()
plt.savefig('xx.png')
