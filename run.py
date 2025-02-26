#!/usr/bin/python3
import sys
from pi import pi
from e import e
from mpmath import mp
from mpmath import zetazero

mp.prec=4096
mp.dps =4096
def get_zero(idx):
    zero = str(zetazero(idx).imag)
    i = zero.index(".")
    zero = zero[i-1:]
    zero = zero.replace(".","")
    return zero

zero1 = get_zero(1)
zero2 = get_zero(2)
c = 0
pi = open("./pi.txt","r")
e = open("./e.txt","r")
while True:
    pp = pi.read(1)
    if (pp  == '.'):
        pp = pi.read(1)
    ee = e.read(1)
    if (ee == '.'):
        ee = e.read(1)
    zz1 = zero1[c]
    zz2 = zero2[c]
    if zz1 == '9' and zz2 == '7':
         input([c,pp,ee,zz1,zz2])
    c =c + 1
