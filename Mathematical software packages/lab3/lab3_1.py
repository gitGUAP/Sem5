import numpy as np
import matplotlib.pyplot as plt

x = np.array([-2, -1, 0, 1, 2, 3, 4, 5])
y = np.array([-28, -23, -20, -17, -12, 7, 46, 104])
n = len(x)


x_ = np.sum(x)/n
y_ = np.sum(y)/n
# Находим b0, b1, b3, b4
A = np.array([
    [1, np.sum(x)/n, np.sum(x**2)/n, np.sum(x**3)/n],
    [np.sum(x)/n, np.sum(x**2)/n, np.sum(x**3)/n, np.sum(x**4)/n],
    [np.sum(x**2)/n, np.sum(x**3)/n, np.sum(x**4)/n, np.sum(x**5)/n],
    [np.sum(x**3)/n, np.sum(x**4)/n, np.sum(x**5)/n, np.sum(x**6)/n]
])
C = np.array([y_, np.sum(x*y)/n, np.sum(x*x*y)/n, np.sum(x*x*x*y)/n])
B = np.linalg.solve(A,C)

print("Оценки коэффициентов регрессии:")
print("b0 = %.2f\nb1 = %.2f\nb2 = %.2f\nb3 = %.2f"%(B[0], B[1], B[2], B[3]))
print("Уравнение регрессии:\ny = %.2f x^3 + %.2f x^2 + %.2f x + %.2f " % (B[3], B[2], B[1], B[0]))

# # Эмпирические значения Y
# y_emp = B[3] * x**3 + B[2] * x**2 + B[1] * x + B[0]
# print(y_emp)
# # ESS - Сумма квадратов отклонений(объясненных регрессией)
# ESS = np.sum((y_emp - y_)**2)
# # TSS - Полная сумма квадратов
# TSS = np.sum((y - y_)**2)
# # Парный коэффициент детерминации
# Rxy = ESS/TSS
# print("\nПарный коэффициент детерминации:\nRxy = %.3f" % Rxy)


# ##Проверка адекватности построенного уравнения регрессии
# # Статистика F
# F = (Rxy * (n-2))/(1 - Rxy)
# print("\nСтатистика F = %.2f" % F)
# # Табличное значение критерия со степенями свободы k1=1 и k2=6
# Fk = 5.99
# print("Fтабл = %.2f" % Fk)
# if F > Fk:
#     print("Поскольку значение F > Fтабл, то коэффициент детерминации статистически значим (уравнение регрессии значимо).")
# else:
#     print("Поскольку значение F < Fтабл, то коэффициент детерминации статистически не значим.")



# S2 = np.dot((y - y_emp).T ,(y - y_emp))/(n-3-1)
# print(S2)
# X = np.array([x**0, x, x**2, x**3])
# print(X.T)
# covMatr = S2*np.linalg.inv(np.dot(X, X.T))

# Sb = np.ones(4)
# for i in range(4):
#     Sb[i] = np.sqrt(covMatr[i][i])

# tB =np.array([
# abs(B[0])/Sb[0],
# abs(B[1])/Sb[1],
# abs(B[2])/Sb[2],
# abs(B[3])/Sb[3]
# ]) 
# t_k = 2.447
# print("\nt0 = %.2f\nt1 = %.2f\nt2 = %.2f\nt3 = %.2f\n" %(tB[0], tB[1], tB[2], tB[3]))
# # tb1 = abs(b1)/(np.sqrt((1-rxy)/(n-2)))
# # print("tb0 = %.2f" %tb0, "tb1 = %.2f" %tb1)
# print("tk = %.2f" %t_k)


# for i in range(4):
#     if tB[i] < t_k:
#         B[i] = 0
# print("b0 = %.2f\nb1 = %.2f\nb2 = %.2f\nb3 = %.2f"%(B[0], B[1], B[2], B[3]))

# ###Повторная проверка модели

# # Эмпирические значения Y
# y_emp_new = B[3] * x**3 + B[2] * x**2 + B[1] * x + B[0]
# # ESS - Сумма квадратов отклонений(объясненных регрессией)
# ESS_new = np.sum((y_emp_new - y_)**2)
# # TSS - Полная сумма квадратов
# TSS_new = np.sum((y - y_)**2)
# # Парный коэффициент детерминации
# Rxy_new = ESS_new/TSS_new
# print("\nПарный коэффициент детерминации:\nRxy = %.3f" % Rxy_new)
# # Статистика F
# F_new = (Rxy_new * (n-2))/(1 - Rxy_new)
# print("\nСтатистика F = %.2f" % F_new)
# # Табличное значение критерия со степенями свободы k1=1 и k2=6
# Fk = 5.99
# print("Fтабл = %.2f" % Fk)
# if F_new > Fk:
#     print("Поскольку значение F > Fтабл, то коэффициент детерминации статистически значим (уравнение регрессии значимо).")
# else:
#     print("Поскольку значение F < Fтабл, то коэффициент детерминации статистически не значим.")




# xplot=np.arange(np.min(x) - 1,np.max(x) + 1,0.01) #Массив значений аргумента
# plt.plot(xplot,B[3] * xplot**3 + B[2] * xplot**2 + B[1] * xplot + B[0]) #Построение графика
# plt.xlabel(r'$x$') #Метка по оси x в формате TeX
# plt.ylabel(r'$f(x)$') #Метка по оси y в формате TeX
# plt.title(r'$y={}x^3   {}$'.format(round(B[3], 2), round(B[0], 2))) #Заголовок в формате TeX
# plt.grid(True) #Сетка
# plt.show() #Показать график