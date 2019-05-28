import sys
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

fileName = 'MySchFairResult.csv';

if sys.argv[1]:
    fileName = sys.argv[1]
    
print(fileName)

dataset = pd.read_csv(fileName)
X = dataset.iloc[:, 1].values
Delay = dataset.iloc[:, 2].values
Throughput = dataset.iloc[:, 3].values
Fairness = dataset.iloc[:, 4].values

# Throughput[:] = [x / 1024 / 1024 for x in Throughput]

plt.figure(1)
plt.plot(X, Delay, color = 'red')
plt.title('Number of users vs Delay')
plt.xlabel('Number of users')
plt.ylabel('Delay (s)')
plt.savefig('Delay.png')

plt.figure(2)
plt.plot(X, Throughput, color = 'red')
plt.title('Number of users vs Throughput')
plt.xlabel('Number of users')
plt.ylabel('Throughput (Mbps)')
plt.savefig('Throughput.png')

plt.figure(3)
plt.plot(X, Fairness, color = 'red')
plt.title('Number of users vs Fairness')
plt.xlabel('Number of users')
plt.ylabel('Fairness')
plt.show()
plt.savefig('Fairness.png')