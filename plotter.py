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
dielec_data = [(float(i)-1)/10 for i in dielectrics.readlines()[0].split(",")[:-1]]
dielectrics.close()

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
        plt.plot(x,data)
        plt.plot(x,dielec_data)
        plt.savefig("./output/" + time + ".png")
        plt.close()

        #save filename for use in gif creation
        filenames.append("./output/" + time + ".png")
infile.close()

#make the gif from images
with imageio.get_writer('./output/movies/e.gif', mode='I') as writer:
    for filename in filenames:
        image = imageio.imread(filename)
        writer.append_data(image)