#!/usr/bin/python3

import sys
import subprocess
from mpmath import mp
from mpmath import zetazero

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
        a=stdout.decode()
        process = subprocess.Popen(["./factorize2", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        b=stdout.decode()
        process = subprocess.Popen(["./factorizea", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        c=stdout.decode()
        process = subprocess.Popen(["./factorizeaa", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        d=stdout.decode()
        bSymmetry = False
        pos = 0
        print("symmetry 1")
        for x in list(zip(a,b)):
            pos = pos + 1
             if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(pos)
                 bSymmetry = True
        pos = 0
        print("symmetry 2")
        for x in list(zip(c,d)):
            pos = pos + 1
            if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(pos)
                 bSymmetry = True
        bAntiSymmetry = False
        pos = 0
        print("symmetry 3")
        for x in list(zip(a,b)):
            pos = pos + 1
            if x[0][0] == x[1][1] and x[0][1] == x[1][0]:
                print(pos)
                bAntiSymmetry = True
        pos = 0
        print("symmetry 4")
        for x in list(zip(c,d)):
            pos = pos + 1
            if x[0][0] == x[1][1] and x[0][1] == x[1][0]:
                print(pos)
                bAntiSymmetry = True
        #if symmetry found decode using Riemann zetazero
        if bAntiSymmetry or bSymmetry:
            zero = get_zero(zero_index)
            print(zero)
            #decode using symmetry positions
        zero_index = zero_index + 1
        input("Enter")
