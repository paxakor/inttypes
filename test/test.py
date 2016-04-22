from random import randint
from subprocess import Popen, PIPE
from sys import argv

n = 1000
s = 80
l = 80

if "-n" in argv:
  n = int(argv[argv.index("-n") + 1])
if "-s" in argv:
  s = int(argv[argv.index("-s") + 1])

errors = 0
proc = Popen(["./test"], stdin = PIPE, stdout = PIPE)
proc.stdin.write(bytes(str(n) + '\n', "ascii"))
for i in range(n):
  a = randint(0, 2**s - 1)
  b = randint(1, 2**s - 1)
  proc.stdin.write(bytes(str(a) + ' ' + str(b) + '\n', "ascii"))
  proc.stdin.flush()
  out = proc.stdout.readline().split()
  if int(out[0]) != (a + b) % 2**l:
    print(a, '+', b, '!=', int(out[0]))
    errors += 1
  if int(out[1]) != (a - b) % 2**l:
    print(a, '-', b, '!=', int(out[1]))
    errors += 1
  if int(out[2]) != (a * b) % 2**l:
    print(a, '*', b, '!=', int(out[2]))
    errors += 1
  if int(out[3]) != (a // b) % 2**l:
    print(a, '/', b, '!=', int(out[3]))
    errors += 1

print(errors, "errors occured")
