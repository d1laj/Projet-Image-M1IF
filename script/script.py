#!python3

import sklearn
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from numpy import genfromtxt
import numpy as np


def rank(idx, tab):
    rk = 1
    for i in tab:
        if i > tab[idx]:
            rk += 1
    return rk

classes = genfromtxt('classes.csv', delimiter=',', dtype=type(""))

ans = genfromtxt('../source/build/answers.csv', delimiter=',', dtype=type(1))
print(ans)

my_data = genfromtxt('../source/build/train.csv', delimiter=',', dtype=type(1.))
#my_data = my_data[:, [0, 2, 3]]
#my_data = my_data[:, np.newaxis]
print(my_data)

clf = SVC(kernel='rbf', gamma=2, C=1, probability=True)
clf = LogisticRegression()

from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(my_data, ans, test_size=.4, random_state=42)

clf.fit(X_train, y_train)
score = clf.score(X_test, y_test)

print(score)

Ans = clf.predict_proba(X_test)
count1 = 0
count2 = 0
for i in range(y_test.size):
    print("Classe : ", classes[y_test[i] - 1], " | probaility : ", Ans[i][y_test[i] - 1], " | rank : ", rank(y_test[i] - 1, Ans[i]))
    if rank(y_test[i] - 1, Ans[i]) <= 10:
        count1 += 1
    if rank(y_test[i] - 1, Ans[i]) <= 2:
        count2 += 1
print("# test rank <= 10 ", count1, count1 / y_test.size)
print("# test rank <= 2 ", count2, count2 / y_test.size)
print("# test ", y_test.size)
#y_result = clf.predict(X_test)
"""
for i in range(y_test.size):
    if y_result[i] == y_test[i]:
        print(y_result[i] == y_test[i], y_test[i], y_result[i], classes[y_result[i] - 1])
    else:
        print(y_result[i] == y_test[i], y_test[i], y_result[i], "\t\t", classes[y_test[i] - 1], " vs ", classes[y_result[i] - 1])
"""
# ratio perimètre aire = 0.119047619048
# + comp conexexes = 0.119047619048 -> pas de gain
# + holes = 0.130952380952
# + PCA = 0.17619047619 -> moins si on enlève composantes connexes 0.17619047619
