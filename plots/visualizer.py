from tkinter import * 
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
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
def plot(ep):
    # the figure that will contain the plot
    fig = Figure(figsize = (15,15),dpi = 100)
    # adding the subplot
    plot1 = fig.add_subplot(111)
    # plotting the graph
    a = np.asarray(preprocess(ep.split()))
    plot1.plot(a[:,:,0].T,a[:,:,1].T)
    plot1.grid()
    # creating the Tkinter canvas
    # containing the Matplotlib figure
    canvas = FigureCanvasTkAgg(fig,master = window)
    canvas.draw()
    # placing the canvas on the Tkinter window
    canvas.get_tk_widget().pack()
    # creating the Matplotlib toolbar
    toolbar = NavigationToolbar2Tk(canvas, window)
    toolbar.update()
    canvas.get_tk_widget().pack()
# the main Tkinter window
window = Tk()
# setting the title 
window.title('Line segment Intersection')
# dimensions of the main window
window.geometry("500x500")
e = '1 3 4 2 3 3 1 1 1 4 2 1 '
# button that displays the plot
plot_button = Button(master = window, command = plot(e),height = 2, width = 10,text = "Plot")
# place the button
# in main window
plot_button.pack()
# run the gui
window.mainloop()