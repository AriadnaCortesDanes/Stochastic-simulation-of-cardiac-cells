import csv
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.patches import Rectangle
from matplotlib.animation import FuncAnimation
import numpy as np

# Function to read data from CSV file
def read_csv(filename):
    with open(filename, 'r') as csvfile:
        csvreader = csv.DictReader(csvfile)
        data = {key: [] for key in csvreader.fieldnames}
        for row in csvreader:
            for key in csvreader.fieldnames:
                data[key].append(float(row[key]))
    return data

def draw_chess_board(ax):
    board_color1 = 'white'
    board_color2 = 'black'
    patches = []

    # Create chess board
    for i in range(8):  # Rows
        for j in range(8):  # Columns
            color = board_color1 if (i + j) % 2 == 0 else board_color2
            patch = Rectangle((j, i), 1, 1, color=color)
            patches.append(patch)
            ax.add_patch(patch)

    ax.set_xlim(0, 8)
    ax.set_ylim(0, 8)
    ax.set_xticks([])
    ax.set_yticks([])
    
    return patches

def update_colors(frame, patches):
    # This function is called for each frame of the animation
    np.random.shuffle(patches)  # Shuffle the patches
    for patch in patches:
        patch.set_color(np.random.choice(['white', 'black', 'red', 'green', 'blue', 'yellow']))
    return patches

def plot_animation(data):
    # Create the main window
    root = tk.Tk()
    root.title("Animated Chess Board")

    fig = Figure(figsize=(6, 6))
    ax = fig.add_subplot(111)

    # Draw chess board and add to tkinter
    patches = draw_chess_board(ax)
    canvas = FigureCanvasTkAgg(fig, master=root)  # A tk.DrawingArea.
    canvas.draw()
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

    # Create animation
    anim = FuncAnimation(fig, update_colors, fargs=(patches,), frames=1000, interval=500, blit=True)

    # Start the GUI event loop
    root.mainloop()

def main():
    data = read_csv(f"csv/PointBackupData_mod_2.csv")
    plot_animation(data)
   

# Example usage
if __name__ == "__main__":
    main()