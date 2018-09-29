import matplotlib.pyplot as plt
import numpy as np
import csv

with open("inp.tsv") as tsvfile:
    tsvreader = csv.reader(tsvfile, delimiter = "\t")
    for line in tsvreader:
        tsv = line

delta = 0.01

a = float(tsv[0])
b = float(tsv[1])
c = float(tsv[2])


x1 = np.arange(-1.0, 1.0, delta)
y1 = 1.0 / (a * np.log(np.absolute(b*x1 +c)))


f = plt.figure()
plt.plot(x1, y1, 'r')

plt.title('Lab 1')
plt.ylabel('y')
plt.xlabel('x')
plt.text(-10, 10, r'$y = \frac{1}{a * \ln(|bx+c|)}$', fontsize  = 16, color = 'black')

plt.grid(True)
plt.show()