import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
def preprocess(arr):
    l = len(arr)/4
    a = []
    c = 0
    for i in range(int(l)):
        pt = []
        pt1 = []
        pt2 = []
        pt1.append(float(arr[c]))
        c+=1
        pt1.append(float(arr[c]))
        c+=1
        pt2.append(float(arr[c]))
        c+=1
        pt2.append(float(arr[c]))
        c+=1
        pt.append(pt1)
        pt.append(pt2)
        a.append(pt)
    return a
curr = 0
df = pd.read_csv("inp.txt",sep = "\n",header=None)
df = np.array(df)
l = int(len(df)/2)
for i in range(int(l)):
    n = int(df[2*i])
    a = df[1+(2*i)][0]
    print(a)