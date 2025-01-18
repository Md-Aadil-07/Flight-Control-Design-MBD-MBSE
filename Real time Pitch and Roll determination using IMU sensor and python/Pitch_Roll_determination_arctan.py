import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Load the csv file
file_path = "plane_motion.csv"
data = pd.read_csv("plane_motion.csv")

# Extract accelerometer (Ax, Ay, Az) and gyroscope (Gx, Gy, Gz) values
Ax, Ay, Az = data['Ax'], data['Ay'], data['Az']
Gx, Gy, Gz = data['Gx'], data['Gy'], data['Gz']

# Calculate pitch and roll 
data['Pitch'] = np.arctan2(Ax, np.sqrt(Ay**2 + Az**2)) * (180 / np.pi)
data['Roll'] = np.arctan2(Ay, np.sqrt(Ax**2 + Az**2)) * (180 / np.pi)


# Display the final DataFrame with Pitch, Roll
print(data.head()) 

# plot graph
plt.plot(data['Pitch'] ,label="pitch",color='r')
plt.plot(data['Roll'] ,label="pitch",color='b')

