import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv
import sys
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

def plot_main_analysis(data,idx):
    fig, axs = plt.subplots(2,sharex=True)
    axs[0].plot(data[f'time_{idx}'],data[f'Volt_{idx}'],label='Volt')
    axs[0].set(xlabel='Time [ms]', ylabel='Membrane potential [mV]')
    axs[0].legend(loc="upper left")
    axs[1].plot(data[f'time_{idx}'],data[f"M_{idx}"],label="m")
    axs[1].plot(data[f'time_{idx}'],data[f"H_{idx}"],label="h")
    axs[1].plot(data[f'time_{idx}'],data[f"J_{idx}"],label="j")
    axs[1].set(xlabel='Time [ms]', ylabel='Gating variables')
    axs[1].legend(loc="upper left")
    for ax in axs:
        ax.label_outer()
    # plt.legend()
    fig.suptitle("Main analysis for Na channels")
    fig, axs = plt.subplots(2,sharex=True)
    axs[0].plot(data['time_0'],data['Volt_0'],label='Volt')
    axs[0].set(xlabel='Time [ms]', ylabel='Membrane potential [mV]')
    axs[0].legend(loc="upper left")
    axs[1].plot(data['time_0'],data["Xr1_0"],label="xr1")
    axs[1].plot(data['time_0'],data["Xr2_0"],label="xr2")
    axs[1].set(xlabel='Time [ms]', ylabel='Gating variables')
    axs[1].legend(loc="upper left")
    for ax in axs:
        ax.label_outer()
    # plt.legend()
    fig.suptitle("Main analysis for Kr channels")
    fig, axs = plt.subplots(2,sharex=True)
    axs[0].plot(data['time_0'],data['Volt_0'],label='Volt')
    axs[0].set(xlabel='Time [ms]', ylabel='Membrane potential [mV]')
    axs[0].legend(loc="upper left")
    axs[1].plot(data['time_0'],data["D_0"],label="d")
    axs[1].plot(data['time_0'],data["F_0"],label="f")
    axs[1].plot(data['time_0'],data["FCa_0"],label="fca")
    axs[1].set(xlabel='Time [ms]', ylabel='Gating variables')
    axs[1].legend(loc="upper left")
    for ax in axs:
        ax.label_outer()
    # plt.legend()
    fig.suptitle("Main analysis for CaL channels")
    fig, axs = plt.subplots(2,sharex=True)
    axs[0].plot(data['time_0'],data['Volt_0'],label='Volt')
    axs[0].set(xlabel='Time [ms]', ylabel='Membrane potential [mV]')
    axs[0].legend(loc="upper left")
    axs[1].plot(data['time_0'],data["R_0"],label="r")
    axs[1].plot(data['time_0'],data["S_0"],label="s")
    axs[1].set(xlabel='Time [ms]', ylabel='Gating variables')
    axs[1].legend(loc="upper left")
    for ax in axs:
        ax.label_outer()
    # plt.legend()
    fig.suptitle("Main analysis for Ito ")
    fig, axs = plt.subplots(2,sharex=True)
    axs[0].plot(data['time_0'],data['Volt_0'],label='Volt')
    axs[0].set(xlabel='Time [ms]', ylabel='Membrane potential [mV]')
    axs[0].legend(loc="upper left")
    axs[1].plot(data['time_0'],data["Xs_0"],label="xs")
    axs[1].set(xlabel='Time [ms]', ylabel='Gating variables')
    axs[1].legend(loc="upper left")
    for ax in axs:
        ax.label_outer()
    # plt.legend()
    fig.suptitle("Main analysis for Iks ")
    fig, axs = plt.subplots(2,sharex=True)
    axs[0].plot(data['time_0'],data['Volt_0'],label='Volt')
    axs[0].set(xlabel='Time [ms]', ylabel='Membrane potential [mV]')
    axs[0].legend(loc="upper left")
    axs[1].plot(data['time_0'],data["G_0"],label="g")
    axs[1].set(xlabel='Time [ms]', ylabel='Gating variables')
    axs[1].legend(loc="upper left")
    for ax in axs:
        ax.label_outer()
    # plt.legend()
    fig.suptitle("Main analysis for Ca Dynamics ")
    
    plt.show()

def plot_main_multianalysis(data):
    # fig, axs = plt.subplots(2,sharex=True)
    for idx in range(10):
        plt.plot(data[f'time_{idx}'],data[f'Volt_{idx}'],label='Volt')
    plt.xlabel("Time [ms]")
    plt.ylabel("Membrane potential [mV]")
    plt.show()

def plot_animation(data):
    n_cells = 100
    delta_x = 0.1
    fig, ax = plt.subplots()

    potentials = [ data[f'Volt_{i}'][0] for i in range(n_cells)]

    x = [delta_x*i for i in range(n_cells)]


    membrane = ax.plot(x,potentials)[0]

 
    ax.set(xlim=[0, delta_x*n_cells], ylim=[-90, 50], xlabel='X [mm]', ylabel='V [mV]')
    ax.legend()


    def update(frame):
        # for each frame, update the data stored on each artist.
        # # update the scatter plot:
        # data = np.stack([x, y]).T
        # scat.set_offsets(data)
        # update the line plot:
        potentials = [ data[f'Volt_{i}'][frame] for i in range(n_cells)]
        membrane.set_ydata(potentials)
        return (membrane)


    ani = animation.FuncAnimation(fig=fig, func=update, frames=1000, interval=200)
    plt.show()



# Main function to plot data
def plot_csv(filename):
    data = read_csv(filename)
    
    plt.plot(data['time_0'],data['Volt_0'])
    for key in data:
        if key != 'time_0':  # Assuming 'x' is the header for x-axis data
            plt.plot(data['time_0'], data[key], label=key)
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('Data from CSV File')
    plt.legend()
    plt.show()


def main():
    data = read_csv(f"csv/PointBackupData_mod_2.csv")
    # plot_main_multianalysis(data)
    # plot_main_analysis(data,sys.argv[1])
    plot_animation(data)
   

# Example usage
if __name__ == "__main__":
    main()