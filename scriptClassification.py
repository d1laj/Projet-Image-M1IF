import sys
fichier = sys.argv[1]
import random
import os
angle = random.random() * 3.1415
scale = random.random() * 3
noise = random.random() * 0.7
print(fichier)
os.system("./imgRotate -i " + fichier  + " -o tmp.pgm -a " + str(angle) + " 2> /dev/null\n")
os.system("./imgScale -i tmp.pgm -o tmp2.pgm -s " + str(scale) + " 2> /dev/null\n")
os.system("./imgAddNoise -i tmp2.pgm -o output/" + fichier[:-4] + "A.pgm" + " -n " + str(noise) + "  2> /dev/null\n")
angle = random.random() * 3.1415
scale = random.random() * 3
noise = random.random() * 0.7
os.system("./imgRotate -i " + fichier  + " -o tmp.pgm -a " + str(angle) + " 2> /dev/null\n")
os.system("./imgScale -i tmp.pgm -o tmp2.pgm -s " + str(scale) + " 2> /dev/null\n")
os.system("./imgAddNoise -i tmp2.pgm -o output/" + fichier[:-4] + "B.pgm" + " -n " + str(noise) + "  2> /dev/null\n")
angle = random.random() * 3.1415
scale = random.random() * 3
noise = random.random() * 0.7
os.system("./imgRotate -i " + fichier  + " -o tmp.pgm -a " + str(angle) + " 2> /dev/null\n")
os.system("./imgScale -i tmp.pgm -o tmp2.pgm -s " + str(scale) + " 2> /dev/null\n")
os.system("./imgAddNoise -i tmp2.pgm -o output/" + fichier[:-4] + "C.pgm" + " -n " + str(noise) + "  2> /dev/null\n")
