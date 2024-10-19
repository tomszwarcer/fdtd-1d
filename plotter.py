import imageio
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
matplotlib.use('Agg')
infile = open("e.csv")
node_num = 200
filenames = []
x = np.linspace(0,node_num-1,node_num)
for line in infile.readlines():
    line =  line[:-1].split(",")
    time = str(line[0])
    data = [float(entry) for entry in line[1:]]
    plt.ylim(0,1)
    plt.plot(x,data)
    plt.savefig("./output/" + time + ".png")
    plt.close()
    filenames.append("./output/" + time + ".png")
with imageio.get_writer('./output/movies/e.gif', mode='I') as writer:
    for filename in filenames:
        image = imageio.imread(filename)
        writer.append_data(image)