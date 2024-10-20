import imageio
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

#Prevent plots opening
matplotlib.use('Agg')

#Open files
infile = open("e.csv")
dielectrics = open("dielectrics.csv")

#Process dielectric data
dielec_data = [float(i) for i in dielectrics.readlines()[0].split(",")[:-1]]
dielectrics.close()
dielec_range = [i for i in range(len(dielec_data)) if dielec_data[i] != dielec_data[i-1]]

node_num = 200
filenames = []

x = np.linspace(0,node_num-1,node_num)
for line in infile.readlines():

    #make csv line into list
    line =  line[:-1].split(",")
    time = str(line[0])

    #Take every fifth line
    if int(time) % 5 == 0:

        #process the field data
        data = [float(entry) for entry in line[1:]]

        #plot
        plt.ylim(-1.1,1.1)
        plt.xlabel("Node position (arb. units)")
        plt.ylabel("E field z component (V/m)")
        plt.plot(x,data)
        plt.axvspan(dielec_range[0],dielec_range[1],alpha = 0.4,color="red")
        plt.text(dielec_range[0]+(dielec_range[1]-dielec_range[0])/6,0.9,"ε_r = " + str(dielec_data[dielec_range[0]]))
        plt.savefig("./output/" + time + ".png")
        plt.close()

        #save filename for use in gif creation
        filenames.append("./output/" + time + ".png")
infile.close()

#make the gif from images
with imageio.get_writer('./output/movies/e.gif', mode='I', loop = 100) as writer:
    for filename in filenames:
        image = imageio.imread(filename)
        writer.append_data(image)