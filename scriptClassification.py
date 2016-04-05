import sys
fichier = sys.argv[1]
import random
angle = random.random() * 3.1415
scale = random.random() * 3
noise = random.random() * 0.7
import os
os.system("./imgRotate -i " + fichier  + " -o tmp.pgm -a " + str(angle) + " 2> /dev/null\n")
os.system("./imgScale -i tmp.pgm -o tmp2.pgm -s " + str(scale) + " 2> /dev/null\n")
os.system("./imgAddNoise -i tmp2.pgm -o output/" + fichier[:-4] + "M.pgm" + " -n " + str(noise) + "  2> /dev/null\n")
