from scipy.stats import chisquare
St = chisquare([5, 11, 16, 26, 21, 14, 7], f_exp=[3.4411, 9.8906, 19.1382, 24.9398, 21.8906, 12.9409, 5.1510], ddof=4)
print('Статистика = ', St[0],'\np-value = ', St[1])
