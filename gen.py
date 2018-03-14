import sys
import random

random.seed(sys.argv[1])

size = int(sys.argv[2])
border = int(sys.argv[3])
lane = "0"
for i in range(size):
	if random.randint(0, border - 1) == 0:
		lane += "1"
	else:
		lane += "0"
print lane + "0"
print random.randint(1, size)