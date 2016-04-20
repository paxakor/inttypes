from random import randint
from subprocess import run
from sys import argv

n = 1000
s = 24

if "-n" in argv:
  n = int(argv[argv.index("-n") + 1])
if "-s" in argv:
  s = int(argv[argv.index("-s") + 1])

errors = 0
for i in range(n):
  a = randint(0, 2**s - 1)
  b = randint(0, 2**s - 1)
  run(["./test"])
