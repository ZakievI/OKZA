import matplotlib.pyplot as plt
import numpy as np

# Чтение данных из файла
data = np.loadtxt('foil.dat')  # или укажите полный путь к файлу
x = data[:, 0]  # первый столбец - x
y = data[:, 1]  # второй столбец - y

data = np.loadtxt('foil_ps.dat')  # или укажите полный путь к файлу
x1 = data[:, 0]  # первый столбец - x
y1 = data[:, 1]  # второй столбец - y

data = np.loadtxt('data.dat')
x2 = data[:, 0]
y2 = data[:, 1]
y3 = []
for i in range(len(x2)):
	y3.append(-1.86)
# Построение графика
plt.figure(1)
plt.plot(x, y, '-', label='xy')  # 'o-' означает точки с линиями
plt.plot(x1, y1, 'r--', label='xy ps')
plt.xlabel('X')
plt.ylabel('Y')
#plt.title('График данных из файла')
plt.legend()
plt.grid(True)

plt.figure(2)
plt.plot(x2, y2, '-', label='f')
plt.plot(x2, y3, '-', label='f')
plt.xlabel('X')
plt.ylabel('Y')
#plt.title('График данных из файла')
plt.legend()
plt.grid(True)

plt.show()