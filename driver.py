#!/usr/bin/python3

import sys
import subprocess
from mpmath import mp
from mpmath import zetazero

def ingest(ll):
    tuples = ll.split(";")
    y = []
    for x in tuples:
        x = x.lstrip("(")
        x = x.rstrip(")")
        x = x.split(",")
        y.append(x)
    return y

def get_zero(zero_index):
     mp.prec=128
     mp.dps=128
     zero = str(zetazero(zero_index).imag)
     idx = zero.index(".")
     zero = zero[idx + 1:]
     return zero

if __name__ == "__main__":
    num = str(sys.argv[1])
    zero_index = 1
    while True:
        process = subprocess.Popen(["./factorize1", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        a=ingest(stdout.decode())[:-1]
        process = subprocess.Popen(["./factorize2", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        b=ingest(stdout.decode())[:-1]
        process = subprocess.Popen(["./factorizea", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        c=ingest(stdout.decode())[:-1]
        process = subprocess.Popen(["./factorizeaa", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        d=ingest(stdout.decode())[:-1]
        bSymmetry = False
        pos = 0
        print(a)
        print(b)
        print(c)
        print(d)
        print("symmetry 1")
        for x in list(zip(a,b)):
            pos = pos + 1
            if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(x)
                 print(pos)
                 bSymmetry = True
        pos = 0
        print("symmetry 2")
        for x in list(zip(c,d)):
            pos = pos + 1
            if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(x)
                 print(pos)
                 bSymmetry = True
        #if symmetry found decode using Riemann zetazero
        if bSymmetry:
            zero = get_zero(zero_index)
            print(zero)
            #decode using symmetry positions
        zero_index = zero_index + 1
        input("Enter")
