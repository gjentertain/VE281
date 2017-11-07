import random

size = 100

f = open('test.in', 'w')
f.write('%d\n%d\n' % (size, size))
f.write('%d %d\n%d %d\n' % (0, 0, size - 1, size - 1))

for i in range(size):
    for j in range(size):
        f.write('%d ' % random.randint(1, 10))
    f.write('\n')

f.close()