#!/usr/bin/env python3

import sys
import os

dossier = sys.argv[1]
os.system("./FeatureExtract -train " + dossier + " classes.csv 2> /dev/null\n")
