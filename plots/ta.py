import subprocess
from tqdm import tqdm
import random
import numpy as np
#n_arr = [5,10,20,50,100,500,1000]
n_arr = [500,1000,1500,2000,2500,5000,10000]
seg_pts = []
for n in n_arr:
    segs = []
    for j in range(4*n):
        segs.append(random.uniform(-100.52,100.78))
    seg_pts.append(segs)
content = ""
i = 0
for seg in seg_pts:
    content += str(n_arr[i])+"\n"
    i +=1
    for s in seg:
        content += str(s)+" "
    content += "\n"
file = open("inp.txt", "a+")
# Saving the array in a text file
#content = str(seg_pts)
file.write(content)
file.close()
#print(f"Running: ")
#.call(["./a > op.txt\n","3 1 3 4 2 3 3 1 1 1 4 2 1"], shell=True)