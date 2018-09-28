import matplotlib.pyplot as plt
import numpy as np
import csv

with open("tsv.tsv") as tsvfile:
    tsvreader = csv.reader(tsvfile, delimiter = "\t")
    for line in tsvreader:
        tsv = line

a = float(tsv[0])
b = float(tsv[1])
c = float(tsv[2])
print(a,b,c)

delta = 0.01


x1 = np.arange(-10.0, -1.0, delta)
y1 = 1.0/(a * np.log(np.absolute(b*x1 +c)))
x2 = np.arange(-1.0 + delta, 1.0, delta)
y2 = 1.0/(a * np.log(np.absolute(b*x2 +c)))
x3 = np.arange(1.0 + delta, 10.0, delta)
y3 = 1.0/(a * np.log(np.absolute(b*x3 +c)))

f = plt.figure()
plt.plot(x1, y1, 'g', x2, y2, 'g', x3, y3, 'g')

plt.title('Lab 1')
plt.ylabel('y')
plt.xlabel('x')
#plt.text(3, 50, r'$y = 1/(a*\ln(abs(b*x+c)))$', fontsize  = 13, color = 'red')

plt.grid(True)
plt.show()