import subprocess
import re
import numpy as np
import matplotlib.pyplot as plt

def get_data(input_program):

    # create a subprocess to pipe the output of the c++ program into python
    proc = subprocess.Popen(['./' + input_program], stdout=subprocess.PIPE)

    temperatures = []
    y_data = []
    x_data = ''
    first_run = True

    # Convert line by line the output from the C++ file into floats using regular expressions. x, y, and temperature
    # data is obtained from the output of the c++ program
    while True:
        line = proc.stdout.readline()
        if first_run:
              x_data = np.array([float(i) for i in re.findall(r'[+\-]?(?:0|[1-9]\d*)(?:\.\d*)?(?:[eE][+\-]?\d+)?', line.decode("utf-8"))])
              first_run = False
        elif line == b'':
            break
        else:
            temp = re.findall(r'[+\-]?(?:0|[1-9]\d*)(?:\.\d*)?(?:[eE][+\-]?\d+)?', line.decode("utf-8"))
            y_data.append(float(temp[0]))
            temperatures.append([float(i) for i in temp[1:]])

    return [x_data, y_data, temperatures]

def plot_data(x, y, temp):

    # convert data to numpy arrays
    temp = np.array(temp)
    y = np.array(y)

    # get the max and min values for the temperatures
    z_min, z_max = 1000.0, np.abs(temp).max()

    fig = plt.figure()
    adjustFigAspect(fig, 3.5)  # second input to the function changes the aspect ratio of the plot
    ax = fig.add_subplot(111)
    data = ax.pcolormesh(x, y, temp, cmap='jet', vmin=z_min, vmax=z_max)  # Creates a contour plot

    #  Everything below makes for a prettier plot.
    ax.axis([x.min(), x.max(), y.min(), y.max()])  # sets the limits of the plot to the limits of the data point
    ax.set_aspect("auto")
    cb = fig.colorbar(data)
    cb.set_cmap("jet")
    cb.set_clim(z_min, z_max)  # set the colorbar limit

    plt.savefig("rosenthal_plot.png")

# Adjusts the aspect ratio of the plot
def adjustFigAspect(fig,aspect=1):
    '''
    Adjust the subplot parameters so that the figure has the correct
    aspect ratio.
    '''
    xsize,ysize = fig.get_size_inches()
    minsize = min(xsize,ysize)
    xlim = .55*minsize/xsize
    ylim = .55*minsize/ysize
    if aspect < 1:
        xlim *= aspect
    else:
        ylim /= aspect
    fig.subplots_adjust(left=.5-xlim,
                        top=.5+ylim,
                        right=.6+xlim,
                        bottom=.5-ylim)


def main(input_program):
    x_distance, y_distance, temperature = get_data(input_program)
    plot_data(x_distance, y_distance, temperature)

if __name__ == "__main__":

    # argparse allows for the python program to take the C++ program as input so I don't have to change it in the python
    # file if I change the C++ file name.
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('input_program')
    args = parser.parse_args()

    main(**vars(args))



