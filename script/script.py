#!python3

import sklearn
from numpy import genfromtxt
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from collections import OrderedDict


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
models = [('Knn 5', KNeighborsClassifier(5)),
          ('Naive Bayes', GaussianNB()),
          ('Logistic Regression', LogisticRegression()),
          ('Linear SVM', SVC(kernel='linear', probability=True)),
          # ('Poly SVM', SVC(kernel='poly', degree=2, probability=True)),
          ('RBF SVM', SVC(kernel='rbf', gamma=2, C=1, probability=True)),
          ('Classification Tree', DecisionTreeClassifier(max_depth=5)),
          ('Random Forest', RandomForestClassifier(max_depth=5, n_estimators=50))]

from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(my_data, ans, test_size=.4, random_state=42)

for model in models:
    print("\n\n######################\n", model[0], "\n######################\n")
    clf = model[1]
    clf.fit(X_train, y_train)
    score = clf.score(X_test, y_test)

    print(score)

    Ans = clf.predict_proba(X_test)
    count1 = 0
    count2 = 0
    tab = [[] for i in range(70)]

    for i in range(y_test.size):
        # print("Classe : ", classes[y_test[i] - 1], " | probaility : ", Ans[i][y_test[i] - 1], " | rank : ", rank(y_test[i] - 1, Ans[i]))
        tab[y_test[i] - 1].append(rank(y_test[i] - 1, Ans[i]))
        if rank(y_test[i] - 1, Ans[i]) <= 10:
            count1 += 1
        if rank(y_test[i] - 1, Ans[i]) <= 2:
            count2 += 1
    print("# test rank <= 10 ", count1, count1 / y_test.size)
    print("# test rank <= 2 ", count2, count2 / y_test.size)
    print("# test ", y_test.size)

    for i in range(70):
        m = 0
        for x in tab[i]:
            m += x
        m /= len(tab[i])
        if m <= 10:
            print("[good] ", classes[i], tab[i], m)
        else:
            print("[bad]  ", classes[i], tab[i], m)
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
