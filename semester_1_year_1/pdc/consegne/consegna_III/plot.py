#!/usr/bin/env python3

import matplotlib.pyplot as plt

size = [256 * i for i in range(1, 7)]
ijk = [4.25816577, 3.29312085, 3.20896222, 3.15912943, 3.14949853, 3.14237436]
kji = [1.07631123, 1.08203933, 1.06267015, 1.06141955, 1.06527994, 1.05059128]
ikj = [57.4955014, 108.736374, 109.473483, 106.526754, 91.8794030, 62.9340609]
jik = [3.98238507, 3.22460052, 3.16497487, 3.10525608, 3.10032125, 3.10292474]
kij = [104.265438, 109.564904, 102.146804, 99.0586966, 77.1264056, 55.2805662]
jki = [1.05782188, 1.06948358, 1.04815055, 1.05814134, 1.05975297, 1.06184116]
block = [71.9737590, 114.067160, 119.214427, 116.769310, 118.611828, 119.326268]

fig1, ax1 = plt.subplots()
fig2, ax2 = plt.subplots()
ax1.plot(size, ijk, label="ijk")
ax1.plot(size, kji, label="kji")
ax1.plot(size, ikj, label="ikj")
ax1.plot(size, jik, label="jik")
ax1.plot(size, kij, label="kij")
ax1.plot(size, jki, label="jki")
ax1.legend()

ax2.plot(size, ikj, label="ikj")
ax2.plot(size, block, label="block")
ax2.legend()

plt.show()
