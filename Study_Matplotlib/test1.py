# -*-coding:utf-8-*-
import numpy as np
import matplotlib.pyplot as plt

# 1.二维单线图
# plt.plot([1, 2, 3, 4, 5], [1, 4, 9, 16, 25], '.', color='b')
# plt.xlabel('X-lable', fontsize=16)
# plt.ylabel('Y-lable', fontsize=16)

# 2.plot参数
# random_numpy = np.arange(0, 10, 0.5)
# m_line = plt.plot(random_numpy, random_numpy)
# plt.setp(m_line, color='r', linestyle=':', linewidth=2.0, alpha=0.5, marker='o', markerfacecolor='b', markersize=5)

# 3.三维图
from mpl_toolkits.mplot3d import axis3d
from mpl_toolkits.mplot3d import axes3d

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

X = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Y = [8, 6, 3, 9, 4, 7, 5, 6, 2, 10]
Z = [1, 5, 6, 8, 4, 6, 2, 8, 4, 6]

Xs = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10]
Ys = [-8, -6, -3, -9, -4, -7, -5, -6, -2, -10]
Zs = [-1, -5, -6, -8, -4, -6, -2, -8, -4, -6]

ax.scatter(X, Y, Z, color='r', marker='o')
ax.scatter(Xs, Ys, Zs, color='b', marker='^')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# ax.plot(X, Y, Z)      # 散点之间的线条

plt.show()