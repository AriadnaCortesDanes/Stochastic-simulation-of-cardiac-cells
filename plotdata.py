import matplotlib.pyplot as plt
import csv
import sys

# Function to read data from CSV file
def read_csv(filename):
    with open(filename, 'r') as csvfile:
        csvreader = csv.DictReader(csvfile)
        data = {key: [] for key in csvreader.fieldnames}
        for row in csvreader:
            for key in csvreader.fieldnames:
                data[key].append(float(row[key]))
    return data

def plot_main_analysis(data):
    fig, axs = plt.subplots(2,sharex=True)
    axs[0].plot(data['time_0'],data['Volt_0'],label='Volt')
    axs[0].set(xlabel='Time [ms]', ylabel='Membrane potential [mV]')
    axs[0].legend(loc="upper left")
    axs[1].plot(data['time_0'],data["M_0"],label="m")
    axs[1].plot(data['time_0'],data["H_0"],label="h")
    axs[1].plot(data['time_0'],data["J_0"],label="j")
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
    plot_main_analysis(data)
   

# Example usage
if __name__ == "__main__":
    main()