from random import randint
from subprocess import Popen, PIPE
from sys import argv

n = 1000
s = 24
l = 48

if "-n" in argv:
  n = int(argv[argv.index("-n") + 1])
if "-s" in argv:
  s = int(argv[argv.index("-s") + 1])

errors = 0
for i in range(n):
  a = randint(0, 2**s - 1)
  b = randint(1, 2**s - 1)
  proc = Popen(["./test", str(a), str(b)], stdout = PIPE, stderr = PIPE)
  proc.wait()
  out, err = proc.communicate()
  out = out.split()
  if int(out[0]) != a + b:
    print(a, '+', b, '!=', int(out[0]))
    errors += 1
  if int(out[1]) != a - b and int(out[1]) != 2**l + (a - b):
    print(a, '-', b, '!=', int(out[1]))
    errors += 1
  if int(out[2]) != a * b:
    print(a, '*', b, '!=', int(out[2]))
    errors += 1
  if int(out[3]) != a // b:
    print(a, '/', b, '!=', int(out[3]))
    errors += 1

print(errors)
