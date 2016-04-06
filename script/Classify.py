#!/usr/bin/env python3

import sys
import os
import sklearn
from numpy import genfromtxt
import numpy as np
from sklearn.ensemble import RandomForestClassifier

fichier = sys.argv[1]
os.system("./FeatureExtract -test " + fichier  + " 2> /dev/null\n")

y_train = genfromtxt('../source/build/answers.csv', delimiter=',', dtype=type(1))

X_train = genfromtxt('../source/build/train.csv', delimiter=',', dtype=type(1.))
X_test = genfromtxt('tmp.csv', delimiter=',', dtype=type(1.))

model = RandomForestClassifier(max_depth=5, n_estimators=50)

clf = model
clf.fit(X_train, y_train)

Ans = clf.predict_proba(X_test)
for i in range(70):
    print("%.4f" % (Ans[0][i]))
