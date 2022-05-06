import matplotlib.pyplot as plt

PointList = []
f = open('.\\data\\output\\voronoi_output1000.txt', 'r')

while True:
    line = f.readline()
    line = line.strip()
    if not line: break
    x_and_y = line.split(',')
    PointList.append(x_and_y)
    print(x_and_y)
f.close()

generatorList = []
g = open(".\\data\\input\\voronoi_test1000.txt")


while True:
    line = g.readline()
    line = line.strip()
    if not line: break
    generator = line.split('\t')
    generatorList.append(generator)
    print(generator)
g.close()

del generatorList[0]

# plt.figure(figsize=(10,10))
plt.axes().set_aspect('equal')

for x1,y1,x2,y2 in PointList:

  plt.plot([float(x1),float(x2)], [float(y1),float(y2)], color='black')

for number, x, y in generatorList:
  plt.scatter(float(x),float(y), color='red')

plt.xlim(-6000,6000)
plt.ylim(-6000,6000)

plt.show()


    







   
