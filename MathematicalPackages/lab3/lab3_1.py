import numpy as np
import matplotlib.pyplot as plt


x = np.array([-5, -3, -2, -1, 0, 1, 2])
y = np.array([17, 27, 20, 9, 2, 6, 25])

n = len(x)
x_ = np.sum(x)/n # x с чертой
y_ = np.sum(y)/n # y с чертой

def coefficients():
    # AB = C
    A = np.array([
        [1, np.sum(x)/n, np.sum(x**2)/n, np.sum(x**3)/n],
        [np.sum(x)/n, np.sum(x**2)/n, np.sum(x**3)/n, np.sum(x**4)/n],
        [np.sum(x**2)/n, np.sum(x**3)/n, np.sum(x**4)/n, np.sum(x**5)/n],
        [np.sum(x**3)/n, np.sum(x**4)/n, np.sum(x**5)/n, np.sum(x**6)/n]
    ]) # x
    C = np.array([y_, np.sum(x*y)/n, np.sum(x*x*y)/n, np.sum(x*x*x*y)/n]) # Значения 
    B = C.dot(np.linalg.inv(A)) # Коэффициенты 
    return B


################################################################################################
################################################################################################
################################################################################################

# 1. Построить уравнение регрессии в виде линейного алгебраического полинома 
print("\t1 step:")
coef = coefficients()

for idx, val in enumerate(coef):
    print("b{} = {:.2f}".format(idx, val))
print("y = {:.2f} x^3 {:+.2f} x^2 {:+.2f} x {:+.2f}".format(coef[3],coef[2],coef[1],coef[0]))

################################################################################################
################################################################################################
################################################################################################

# 2. Проверить адекватность построенного уравнения регрессии экспериментальным данным по критерию Фишера
print("\t2 step:")

# Эмпирические значения
y_emp = coef[3] * x**3 + coef[2] * x**2 + coef[1] * x + coef[0]

# ESS - Сумма квадратов отклонений(объясненных регрессией)
ESS = np.sum((y_emp - y_)**2)
# TSS - Полная сумма квадратов
TSS = np.sum((y - y_)**2)
Rxy = ESS/TSS

print("Pair coefficient of determination:")
print("Rxy = {:.2f}".format(Rxy))

# Проверка адекватности построенного уравнения регрессии
# Статистика F
F = (Rxy * (n-4))/(1 - Rxy)
print("F = {:.2f}".format(F))

Fk = 5.99
print("Fk = {:.2f}".format(Fk))

if F > Fk:
    print("Since the value of F > Fk, the coefficient of determination is statistically significant.")
else:
    print("Since the value of F <Fk, the coefficient of determination is not statistically significant.")

################################################################################################
################################################################################################
################################################################################################

# 3. Выполнить селекцию факторов по критерию Стьюдента при таком же уровне значимости
print("\t3 step:")

# S2 - Несмещённая оценка дисперсии
S2 = np.dot((y - y_emp).T ,(y - y_emp))/(n-3-1)
X = np.array([x**0, x, x**2, x**3])

# V - ковариационная матрица
V = S2*np.linalg.inv(np.dot(X, X.T))

# Sb - отклонения параметров модели
Sb = np.ones(4)
for i in range(4):
    Sb[i] = np.sqrt(V[i][i])

# t-критерий Стьюдента
tB =np.array([
    abs(coef[0])/Sb[0],
    abs(coef[1])/Sb[1],
    abs(coef[2])/Sb[2],
    abs(coef[3])/Sb[3]
]) 

# tk - табличное значение 
tk = 2.447

print("Student's t-test:")
for idx, val in enumerate(tB):
    print("t{} = {:.2f}".format(idx, val))

print("Tabular value:")
print("tk = {:.2f}".format(tk))

#Проверка рассчитанных значений
for i in range(len(tB)):
    if tB[i] < tk:
        coef[i] = 0
        print("Delete b{}: {} < {}".format(i, tB[i], tk))

################################################################################################
################################################################################################
################################################################################################

xplot=np.arange(np.min(x) - 1,np.max(x) + 1,0.01)
plt.plot(xplot,coef[3] * xplot**3 + coef[2] * xplot**2 + coef[1] * xplot + coef[0])

plt.xlabel(r'$x$')
plt.ylabel(r'$f(x)$')
plt.title(r'$y = {:.2f}x^3{:+.2f}x^2{:+.2f}x{:+.2f}$'.format(coef[3],coef[2],coef[1], coef[0]))

plt.grid(True)
plt.show()



