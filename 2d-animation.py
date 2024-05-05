import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv
import sys
import numpy as np

import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def draw_data(data):
    fig = Figure(figsize=(6, 6))
    ax = fig.add_subplot(111)

    board_color = 'white', 'black'
    for i in range(50):  # Rows
        for j in range(50):  # Columns
            ax.add_patch(plt.Rectangle((j, i), 1, 1, fill=True, color=board_color[(i+j) % 2]))

    ax.set_xlim(0, 50)
    ax.set_ylim(0, 50)
    ax.set_xticks([])
    ax.set_yticks([])

    return fig

def plot_board(data):
    root = tk.Tk()
    root.title("Potential wave in cardiac tissue")

    fig = draw_data(data)
    canvas = FigureCanvasTkAgg(fig, master=root)  # tk.DrawingArea.
    canvas.draw()
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
    root.mainloop()

def plot_animation(data):
    plot_board(data)

# Function to read data from CSV file
def read_csv(filename):
    with open(filename, 'r') as csvfile:
        csvreader = csv.DictReader(csvfile)
        data = {key: [] for key in csvreader.fieldnames}
        for row in csvreader:
            for key in csvreader.fieldnames:
                data[key].append(float(row[key]))
    return data

def main():
    data = read_csv(f"csv/PointBackupData_mod_2.csv")
    plot_animation(data)
   

# Example usage
if __name__ == "__main__":
    main()