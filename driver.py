#!/usr/bin/python3

import sys
import subprocess
from mpmath import mp
from mpmath import zetazero

def complement(x):
    nn = ""
    for y in x:
        nn = nn + str((11-int(y)) % 10)
    return nn

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
    cnum = complement(num)
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
        process = subprocess.Popen(["./factorize1", cnum, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        p=ingest(stdout.decode())[:-1]
        process = subprocess.Popen(["./factorize2", cnum, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        q=ingest(stdout.decode())[:-1]
        process = subprocess.Popen(["./factorizea", cnum, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        m=ingest(stdout.decode())[:-1]
        process = subprocess.Popen(["./factorizeaa", cnum, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        n=ingest(stdout.decode())[:-1]
        bSymmetry1 = False
        pos = 0
        print(a)
        print(b)
        print(c)
        print(d)
        print(p)
        print(q)
        print(m)
        print(n)
        print("symmetry 1")
        for x in list(zip(a,b)):
            pos = pos + 1
            if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(x)
                 print(pos)
                 bSymmetry = True
        pos = 0
        print("symmetry 2")
        bSymmetry2 = False
        for x in list(zip(c,d)):
            pos = pos + 1
            if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(x)
                 print(pos)
                 bSymmetry2 = True
        print("symmetry 3")
        bSymmetry3 = False
        for x in list(zip(p,q)):
            pos = pos + 1
            if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(x)
                 print(pos)
                 bSymmetry3 = True
        pos = 0
        print("symmetry 4")
        bSymmetry4 = False
        for x in list(zip(m,n)):
            pos = pos + 1
            if x[0][0] == x[1][0] and x[0][1] == x[1][1]:
                 print(x)
                 print(pos)
                 bSymmetry4 = True
        #if symmetry found decode using Riemann zetazero
        print(zero_index)
        if bSymmetry1 == True and bSymmetry2 == True and bSymmetry3 == True and bSymmetry4 == True:
            input("Enter")
            #decode using symmetry positions
        zero_index = zero_index + 1
