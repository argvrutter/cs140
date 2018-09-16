import argparse, sys

f = open(sys.argv[1])

numbers = f.read().split();
for i, num in enumerate(numbers):
    if not num.isdigit():
        print(num, "index:", i)
    if 0 <= num <= 255:
        print(num, "index:", i)

f.close()
