from tkinter import * 
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
def plot():
    # the figure that will contain the plot
    fig = Figure(figsize = (25,25),dpi = 100)
    # adding the subplot
    plot1 = fig.add_subplot(111)
    # plotting the graph
    df = pd.read_csv('pts.csv')
    df1 = pd.read_csv('segs.csv')
    for i in range(len(df1)):
        plot1.plot(np.asarray(df1.iloc[i,0:2]).T,np.asarray(df1.iloc[i,2:4]).T,c='black')
    plot1.scatter(np.asarray(df.iloc[:,0]),np.asarray(df.iloc[:,1]),c='red',marker = 'o')
    plot1.set_xlabel('X axis')
    plot1.set_ylabel('Y axis')
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
window.geometry("800x800")
# button that displays the plot
#plot_button = Button(master = window, command = plot(),height = 2, width = 10,text = "Plot")
# place the button
# in main window
#plot_button.pack()
plot()
# run the gui
window.mainloop()