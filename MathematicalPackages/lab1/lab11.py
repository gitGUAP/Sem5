import matplotlib.pyplot as plt
import numpy as np
import csv

with open("inp.tsv") as tsvfile:
    tsvreader = csv.reader(tsvfile, delimiter = "\t")
    for line in tsvreader:
        tsv = line

delta = 0.001

a = float(tsv[0])
b = float(tsv[1])
c = float(tsv[2])

m1 = (-1 - c) / b
m2 = (1 - c) / b


r1 = min(m1, m2)
r2 = max(m1, m2)

print(r1,r2)

x1 = np.arange(-10.0, r1, delta)
y1 = 1.0 / (a * np.log(np.absolute(b*x1 +c)))

x2 = np.arange(r1, r2, delta)
y2 = 1.0 / (a * np.log(np.absolute(b*x2 + c)))

x3 = np.arange(r2, 10.0, delta)
y3 = 1.0 / (a * np.log(np.absolute(b*x3 +c)))

plt.plot(x1, y1, 'r')
plt.plot(x2, y2, 'g')
plt.plot(x3, y3, 'b')

plt.title('Lab 1')
plt.ylabel('y')
plt.xlabel('x')
plt.text(-10, 8, r'$y = \frac{1}{a * \ln(|bx+c|)}$', fontsize  = 16, color = 'black')

d = abs(r2 + r1) / 2

print(d)
axes = plt.gca()
axes.set_xlim([-c - 10, c + 10])
axes.set_ylim([-10,10])

plt.grid(True)
plt.show()