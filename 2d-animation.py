import matplotlib.pyplot as plt
import csv
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np

def draw_data(data, frame, fig, ax):
    ax.clear()  # Clear the previous drawing

    for i in range(20):  # Rows
        for j in range(20):  # Columns
            color_from_data = 1- abs(data[f'Volt_{i}_{j}'][frame]) / 100
            ax.add_patch(plt.Rectangle((i, j), 1, 1, fill=True, color=(color_from_data, 0, 0)))

    ax.set_xlim(0, 20)
    ax.set_ylim(0, 20)
    ax.set_xticks([])
    ax.set_yticks([])

def update_figure(frame, data, canvas, fig, ax, root):
    if frame >= 1000:
        print("Animation Completed")
        return
    print(frame)
    draw_data(data, frame, fig, ax)
    canvas.draw()
    root.after(1, update_figure, frame + 1, data, canvas, fig, ax, root)  # update every 100 milliseconds

def plot_board(data):
    root = tk.Tk()
    root.title("Potential wave in cardiac tissue")

    # Create figure and axes
    fig = Figure(figsize=(6, 6))
    ax = fig.add_subplot(111)
    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

    update_figure(0, data, canvas, fig, ax, root)  # Start the animation

    root.mainloop()

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
    data = read_csv("csv/PointBackupData_mod_2.csv")
    plot_board(data)

# Example usage
if __name__ == "__main__":
    main()
